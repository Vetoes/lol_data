
cmake_minimum_required(VERSION 3.14)
project(LeagueClient VERSION 1.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find nlohmann_json package
find_package(nlohmann_json 3.2.0 REQUIRED)

# Add executable
add_executable(league_client 
    liveclient.cpp
)

# Link libraries
target_link_libraries(league_client PRIVATE
    nlohmann_json::nlohmann_json
)

# Add filesystem library for GCC versions that need it
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(league_client PRIVATE stdc++fs)
endif()
