cmake_minimum_required(VERSION 3.26)
project(moreTest)

set(CMAKE_CXX_STANDARD 14)

add_executable(moreTest main.cpp
        HarmonyTrends.h
)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/SFML-2.6.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/SFML-2.6.1/include/SFML)
target_link_libraries(moreTest sfml-system sfml-window sfml-graphics sfml-audio)