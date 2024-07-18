cmake_minimum_required(VERSION 2.84 FATAL_ERROR)
project(progetto_finale)

set(CMAKE_CXX_STANDARD 11)

set (CMAKE_CXX_FLAGS "-O2")

include_directories(include)

add_library(${PROJECT_NAME} SHARED
        src/Casella.cpp
        src/Tabellone.cpp
        src/Terreno.cpp
        src/Gioco.cpp
        src/Giocatore.cpp
        src/GiocatoreComputer.cpp
        src/GiocatoreUmano.cpp
)

add_executable(main src/main.cpp)

target_link_libraries(main ${PROJECT_NAME})


