#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <string>
using json = nlohmann::json;
// read from liveclientdata_sample.json
// make champion class data
class live_client_user{
  std::string champion_name;
  std::string champion_passive;
  

  struct q{
    int abilityLevel =0;
    std::string displayName = "";
    std::string id = "";
    std::string rawDescription = "";
    std::string rawDisplayName = "";
  };
  struct w{
    int abilityLevel = 0;
    std::string displayName = "";
    std::string id = "";
    std::string rawDescription = "";
    std::string rawDisplayName = "";
  };
  struct e{
    int abilityLevel = 0;
    std::string displayName = "";
    std::string id = "";
    std::string rawDescription = "";
    std::string rawDisplayName = "";
  };
  struct r{
    int abilityLevel = 0;
    std::string displayName = "";
    std::string id = "";
    std::string rawDescription = "";
    std::string rawDisplayName = "";
  };

};

