cmake_minimum_required(VERSION 3.10)
project(Otrio_Projet)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES "src/*.cpp")

# Exclure temporairement les fichiers non terminés
list(FILTER SOURCES EXCLUDE REGEX ".*/Plateau\\.cpp$")

add_executable(Otrio_Game ${SOURCES})
target_include_directories(Otrio_Game PRIVATE include)
