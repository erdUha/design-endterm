cmake_minimum_required(VERSION 3.15)

project(PartA VERSION 1.0 LANGUAGES CXX)
project(PartB VERSION 1.0 LANGUAGES CXX)
project(PartC VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "Disable yaml-cpp tests")
set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "Disable yaml-cpp tools")
set(CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/config/messages.yaml")
set(CONFIG_DEST "${CMAKE_CURRENT_BINARY_DIR}/config/messages.yaml")
add_subdirectory(libs/yaml-cpp)

configure_file(${CONFIG_FILE} ${CONFIG_DEST} COPYONLY)

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
target_link_libraries(PartC PRIVATE yaml-cpp)
