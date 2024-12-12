import requests
import json
from datetime import datetime
import os
from dotenv import load_dotenv

# .env 파일에서 API 키 로드
load_dotenv()
RIOT_API_KEY = os.getenv('RIOT_API_KEY')

class RiotAPI:

    def __init__(self, region="kr", routing="asia"):
        """
        region options: kr, jp1, na1, euw1, eun1, oc1, br1, la1, la2, ru, tr1
        routing options: asia, americas, europe, sea
        """
        self.api_key = RIOT_API_KEY
        self.region = region
        self.routing = routing
        self.base_url = f"https://{region}.api.riotgames.com"
        self.routing_url = f"https://{routing}.api.riotgames.com"
        self.headers = {
            "X-Riot-Token": self.api_key
        }

    def get_summoner_by_name(self, game_name, tag_line):
        """
        소환사 이름과 태그라인으로 정보 검색
        game_name: 게임 닉네임
        tag_line: 태그라인 (예: KR1, NA1 등)
        """
        endpoint = f"/riot/account/v1/accounts/by-riot-id/{game_name}/{tag_line}"
        response = requests.get(f"{self.routing_url}{endpoint}", headers=self.headers)
        account_data = response.json()
        
        return account_data

    def get_match_ids(self, puuid, count=20, queue=None, start_time=None, end_time=None):
        """
        PUUID로 매치 ID 목록 가져오기
        Args:
            puuid: 플레이어 PUUID
            count: 가져올 매치 수 (최대 100)
            queue: 큐 타입 (예: 420=솔랭, 440=자유랭크, 430=일반게임)
            start_time: 시작 시간 (Unix timestamp)
            end_time: 종료 시간 (Unix timestamp)
        """
        endpoint = f"/lol/match/v5/matches/by-puuid/{puuid}/ids"
        params = {'count': count}

        if queue:
            params['queue'] = queue
        if start_time:
            params['startTime'] = start_time
        if end_time:
            params['endTime'] = end_time

        response = requests.get(f"{self.routing_url}{endpoint}", 
                                headers=self.headers,
                                params=params)
        return response.json()

    def get_match_detail(self, match_id):
        """
        매치 ID로 게임 상세 정보 가져오기
        """
        endpoint = f"/lol/match/v5/matches/{match_id}"
        response = requests.get(f"{self.routing_url}{endpoint}", 
                              headers=self.headers)
        return response.json()


def main():
    # API 키가 없으면 종료
    if not RIOT_API_KEY:
        print("Error: RIOT_API_KEY not found in .env file")
        return

    api = RiotAPI()
    
    try:
        # 챔피언 데이터 가져오기
        # 소환사 검색 예시
        game_name = input("Enter game name: ")
        tag_line = input("Enter tagline (e.g., KR1): ")
        summoner = api.get_summoner_by_name(game_name, tag_line)

        print(f"\nSummoner info for {summoner}:")
        print(json.dumps(summoner, indent=2))

        if 'puuid' in summoner:
            puuid = summoner['puuid']
            print(f"\nFetching recent matches for {game_name}...")

            #bring match id
            match_ids = api.get_match_ids(puuid,count=5,queue=420,start_time=0)
            print("\nRecent match IDs:")

            for match_id in match_ids:
                print(match_id)

            if match_ids:
                print("\nFetching details for the most recent match...")
                match_detail = api.get_match_detail(match_ids[0])
                print(json.dumps(match_detail,indent=2))


                
    except requests.exceptions.RequestException as e:
        print(f"Error making API request: {e}")
    except json.JSONDecodeError as e:
        print(f"Error decoding JSON response: {e}")
    except Exception as e:
        print(f"Unexpected error: {e}")

if __name__ == "__main__":
    main()
