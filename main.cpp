#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#define CHAMPIONS_NAME "name"

// Use the nlohmann namespace for convenience
using json = nlohmann::json;

class Champions {

  /*std::string name;*/

  //
  //health
  //healthregen
  //mana
  //manaregen
  //armor
  //magicresistance
  //attackdamage
  //movespeed
  //acquisitionradius
  //selectionradius
  //


public:

  const std::string name;
  const json stats;

  Champions(const std::string& champions_name,const json stats) :
  name(champions_name),stats(stats){}
  /**/
  /*void setName(const std::string& champions_name){*/
  /*  name =  champions_name;*/
  /*}*/
} ;
std::vector<Champions> champions_list;

json readJsonFromFile(const std::string& filePath) {
    std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        throw std::runtime_error("Failed to open the file: " + filePath);
    }

    json jsonData = json::parse(inputFile);
    /*inputFile >> jsonData;  // Read and parse JSON*/
    return jsonData;
}

int main() {
  /*std::cout << "Enter Champion" << std::endl;*/
  /*std::string filepath;*/
  /*std::getline(std::cin,filepath);*/
  //never change data
  const json data = readJsonFromFile("14_23_lol.json");

  for(auto& [champion_name, champion_data]: data.items()){
    champions_list.emplace_back(Champions(champion_name,champion_data["stats"]["attackSpeed"]));
  }

  /*while(std::getline(champions_name,line)){*/
  /*  if(!line.empty()){*/
  /*    champions_list.push_back(Champions(line));*/
  /*    num_of_champs+=1;*/
  /*  }*/
  /*}*/

  /*for(auto& champion : champions_list){*/
  /*  std::cout << champion.name << std::endl;*/
  /*  std::cout << champion.stats << std::endl;*/
  /*std::cout << num_of_champs << std::endl;*/
  /*}*/


  
  /*std::cout << champions_list[2].name << std::endl;*/

  /*std::cout << champions_list["Aatrox"] ;*/
 
  /*std::cout << champions_name << std::endl;*/

  /*std::cout << data["Aatrox"].dump(4) << std::endl;*/

  return 0;
}
