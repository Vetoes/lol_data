#include <nlohmann/json.hpp>
#include <string>
#include <iostream>
#include <fstream>

using json = nlohmann::json;


  class ChampionAbility {
  public:
      int abilityLevel;
      std::string displayName;
      std::string id;
      std::string rawDescription;
      std::string rawDisplayName;

// Constructor
ChampionAbility() : abilityLevel(0) {}

// Parse from JSON
void fromJson(const json& j) {
    abilityLevel = j["abilityLevel"];
    displayName = j["displayName"];
    id = j["id"];
    rawDescription = j["rawDescription"];
    rawDisplayName = j["rawDisplayName"];
}
};

class Champion {
private:
std::string championName;
std::string passive;
ChampionAbility q, w, e, r;
bool isDead;
double currentHealth;
double maxHealth;

public:
Champion() : isDead(false), currentHealth(0), maxHealth(0) {}

// Getters
const std::string& getName() const { return championName; }
const std::string& getPassive() const { return passive; }
const ChampionAbility& getQ() const { return q; }
const ChampionAbility& getW() const { return w; }
const ChampionAbility& getE() const { return e; }
const ChampionAbility& getR() const { return r; }
bool getIsDead() const { return isDead; }
double getCurrentHealth() const { return currentHealth; }
double getMaxHealth() const { return maxHealth; }

// Load champion data from JSON
void loadFromJson(const json& data) {
    try {
        auto activePlayer = data["activePlayer"];
        auto abilities = activePlayer["abilities"];

        // Load abilities
        q.fromJson(abilities["Q"]);
        w.fromJson(abilities["W"]);
        e.fromJson(abilities["E"]);
        r.fromJson(abilities["R"]);

        // Load champion stats
        if (data.contains("activePlayer")) {
            championName = data["activePlayer"]["summonerName"];
            currentHealth = data["activePlayer"]["championStats"]["currentHealth"];
            maxHealth = data["activePlayer"]["championStats"]["maxHealth"];
        }

    } catch (const json::exception& e) {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
    }
}

// Print champion information
void printInfo() const {
    std::cout << "Champion: " << championName << std::endl;
    std::cout << "Health: " << currentHealth << "/" << maxHealth << std::endl;
    std::cout << "\nAbilities:" << std::endl;
    
    std::cout << "Q - " << q.displayName << " (Level " << q.abilityLevel << ")" << std::endl;
    std::cout << "W - " << w.displayName << " (Level " << w.abilityLevel << ")" << std::endl;
    std::cout << "E - " << e.displayName << " (Level " << e.abilityLevel << ")" << std::endl;
    std::cout << "R - " << r.displayName << " (Level " << r.abilityLevel << ")" << std::endl;
}
};

// Main interface class
class LiveClientUser {
private:
Champion champion;

public:
bool loadChampionData(const std::string& filename) {
    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Could not open file: " << filename << std::endl;
            return false;
        }

        json data = json::parse(file);
        champion.loadFromJson(data);
        return true;

    } catch (const std::exception& e) {
        std::cerr << "Error loading champion data: " << e.what() << std::endl;
        return false;
    }
}

const Champion& getChampion() const { return champion; }
};

/*int main() {*/
/*    LiveClientUser client;*/
/**/
/*    if (client.loadChampionData("liveclientdata_sample.json")) {*/
/*        const Champion& champ = client.getChampion();*/
/*        champ.printInfo();*/
/*    }*/
/**/
/*    return 0;*/
/*}*/
