cmake_minimum_required(VERSION 3.10)
project(Otrio_Projet)

set(CMAKE_CXX_STANDARD 17)

# Trouver SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(Otrio_Game ${SOURCES})
target_include_directories(Otrio_Game PRIVATE include)

# Lier SFML au projet
target_link_libraries(Otrio_Game PRIVATE sfml-graphics sfml-window sfml-system)
