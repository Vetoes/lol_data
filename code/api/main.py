
import requests
import json
from datetime import datetime
import os
from dotenv import load_dotenv

# .env 파일에서 API 키 로드
load_dotenv()
RIOT_API_KEY = os.getenv('RIOT_API_KEY')

class RiotAPI:
    def __init__(self):
        self.api_key = RIOT_API_KEY
        self.base_url = "https://kr.api.riotgames.com"
        self.headers = {
            "X-Riot-Token": self.api_key
        }

    def get_champion_data(self):
        """
        Data Dragon에서 최신 챔피언 데이터 가져오기
        """
        version_url = "https://ddragon.leagueoflegends.com/api/versions.json"
        versions = requests.get(version_url).json()
        latest_version = versions[0]

        champion_url = f"http://ddragon.leagueoflegends.com/cdn/{latest_version}/data/ko_KR/champion.json"
        response = requests.get(champion_url)
        return response.json()

    def get_summoner_by_name(self, summoner_name):
        """
        소환사 이름으로 정보 검색
        """
        endpoint = f"/lol/summoner/v4/summoners/by-name/{summoner_name}"
        response = requests.get(f"{self.base_url}{endpoint}", headers=self.headers)
        return response.json()

    def get_match_history(self, puuid, count=5):
        """
        특정 소환사의 최근 게임 기록 가져오기
        """
        matches_url = f"https://asia.api.riotgames.com/lol/match/v5/matches/by-puuid/{puuid}/ids?count={count}"
        match_ids = requests.get(matches_url, headers=self.headers).json()
        
        matches = []
        for match_id in match_ids:
            match_url = f"https://asia.api.riotgames.com/lol/match/v5/matches/{match_id}"
            match_data = requests.get(match_url, headers=self.headers).json()
            matches.append(match_data)
        
        return matches

def main():
    # API 키가 없으면 종료
    if not RIOT_API_KEY:
        print("Error: RIOT_API_KEY not found in .env file")
        return

    api = RiotAPI()
    
    try:
        # 챔피언 데이터 가져오기
        print("Fetching champion data...")
        champion_data = api.get_champion_data()
        
        # 챔피언 목록 저장
        with open('champion_data.json', 'w', encoding='utf-8') as f:
            json.dump(champion_data, f, ensure_ascii=False, indent=2)
        print("Champion data saved to champion_data.json")

        # 소환사 검색 예시
        summoner_name = input("Enter summoner name: ")
        summoner = api.get_summoner_by_name(summoner_name)
        print(f"\nSummoner info for {summoner_name}:")
        print(json.dumps(summoner, indent=2))

        # 최근 게임 기록 가져오기
        if 'puuid' in summoner:
            print(f"\nFetching recent matches for {summoner_name}...")
            matches = api.get_match_history(summoner['puuid'], count=3)
            
            # 매치 데이터 저장
            with open('recent_matches.json', 'w', encoding='utf-8') as f:
                json.dump(matches, f, ensure_ascii=False, indent=2)
            print("Match data saved to recent_matches.json")

    except requests.exceptions.RequestException as e:
        print(f"Error making API request: {e}")
    except json.JSONDecodeError as e:
        print(f"Error decoding JSON response: {e}")
    except Exception as e:
        print(f"Unexpected error: {e}")

if __name__ == "__main__":
    main()
