#ifndef CHAMPIONS_H
#define CHAMPIONS_H

#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Champions {
public:
    Champions(const std::string& champions_name, const json& champion_stats) 
        : name(champions_name), stats(champion_stats) {}

    std::string name;
    json stats;

    // 챔피언 정보 출력을 위한 함수
    void print_stats() const {
        std::cout << "Champion: " << name << std::endl;
        std::cout << "Stats: " << stats.dump(2) << std::endl;
    }

    // 챔피언 데이터 로드를 위한 정적 함수
    static std::vector<Champions> load_champions(const json& data) {
        std::vector<Champions> champions;
        for (const auto& [champion_name, champion_data] : data["data"].items()) {
            champions.emplace_back(champion_name, champion_data["stats"]);
        }
        return champions;
    }
};

#endif // CHAMPIONS_H
