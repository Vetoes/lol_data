#include <cstddef>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <ostream>
#include <string>
#include <vector>


/* 
 *
 * get local data
 *
 * read from file lockfile usually 
 *
 * C/riot/league of legends/lockfile
 * get data delimiter ":"
*
*/
//lockfile을 읽은뒤  ":" 을 만날때마다 문자열을 나눈다.

std::string read_lockfile() {
    const char* appdata = getenv("LOCALAPPDATA");
    if (!appdata) {
        throw std::runtime_error("Cannot find LOCALAPPDATA environment variable");
    }

    std::filesystem::path lockfile_path = std::filesystem::path(appdata) / 
        "Riot Games" / "League of Legends" / "lockfile";

    if (!std::filesystem::exists(lockfile_path)) {
        throw std::runtime_error("Lockfile not found. Is League of Legends running?");
    }

    std::ifstream input_file(lockfile_path);
    if (!input_file.is_open()) {
        throw std::runtime_error("Cannot open lockfile");
    }

    std::string content;
    std::getline(input_file, content);
    return content;
}

std::vector<std::string> split_string (std::string lockfile){
  
  std::vector<std::string> tokens; 
  std::string token;
  std::string delimiter = ":";
  size_t pos_end ;
  size_t pos_start = 0;
  size_t delim_len =  delimiter.length();

  while((pos_end = lockfile.find(delimiter,pos_start)) != std::string::npos)
  {
    
    token = lockfile.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    tokens.push_back(token);

  }
  tokens.push_back(lockfile.substr(pos_start));
  return tokens;
}

int main(){
  std::ifstream input_file("lockfile");
  std::string lockfile;
  input_file >>lockfile;

  std::vector<std::string> splited;
  splited = split_string(lockfile);

  std::string port = splited[1];
  std::string auth_token = splited[2];

  std::string base_url = "https://127.0.0.1:" + port + "/liveclientdata/allgamedata";
  std::cout << base_url << std::endl;

}
