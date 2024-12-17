#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <sstream>

// CURL 콜백 함수
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// 문자열 분할 함수
std::vector<std::string> split(const std::string& str, char delim) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    // lockfile 읽기
    std::ifstream file("C:/Riot Games/League of Legends/lockfile");
    if (!file.is_open()) {
        std::cerr << "Cannot open lockfile" << std::endl;
        return 1;
    }

    std::string lockfile_content;
    std::getline(file, lockfile_content);
    file.close();

    // lockfile 데이터 파싱
    auto lockfile_data = split(lockfile_content, ':');
    if (lockfile_data.size() < 4) {
        std::cerr << "Invalid lockfile format" << std::endl;
        return 1;
    }

    /*std::string port = lockfile_data[2];*/
    std::string port = "2999";
    std::string auth_token = lockfile_data[3];

    // URL 생성
    std::string url = "https://127.0.0.1:" + port + "/liveclientdata/allgamedata";

    // CURL 초기화
    CURL* curl = curl_easy_init();
    std::string response_data;

    if (curl) {
        struct curl_slist* headers = NULL;
        std::string auth_header = "Authorization: Basic " + auth_token;
        headers = curl_slist_append(headers, auth_header.c_str());

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        // 요청 실행
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            
            if (response_code == 200) {
                std::cout << "Response: " << response_data << std::endl;
            } else {
                std::cerr << "Error: " << response_code << std::endl;
            }
        }

        // 정리
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    return 0;
}

