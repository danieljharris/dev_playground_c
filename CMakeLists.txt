cmake_minimum_required(VERSION 3.22)

project(dev_playground_c LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(playground
	src/main.cpp
	src/seed/seed.cpp
	src/expected/expected.cpp
)

target_include_directories(playground PRIVATE ${PROJECT_SOURCE_DIR}/src)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(playground PRIVATE spdlog::spdlog)
