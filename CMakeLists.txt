cmake_minimum_required(VERSION 3.16)

project(dev_playground_c LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(playground
	src/main.cpp
	src/challenge1/challenge.cpp
)

target_include_directories(playground PRIVATE ${PROJECT_SOURCE_DIR}/src)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(playground PRIVATE spdlog::spdlog)

set_target_properties(playground PROPERTIES SUFFIX ".exe")
