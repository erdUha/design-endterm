cmake_minimum_required(VERSION 3.15)

project(PartA VERSION 1.0 LANGUAGES CXX)
project(PartB VERSION 1.0 LANGUAGES CXX)
project(PartC VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(PartA
  src/partA/main.cpp
)

add_executable(PartB
  src/partB/main.cpp
)

add_executable(PartC
  src/partC/main.cpp
)

target_include_directories(PartA PUBLIC include)
target_include_directories(PartB PUBLIC include)
target_include_directories(PartC PUBLIC include)
