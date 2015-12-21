cmake_minimum_required(VERSION 3.3)
project(BattleWorms)

#flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic -Wextra")

#settings
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

#recurse into subdirectories
add_subdirectory(src)
