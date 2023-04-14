cmake_minimum_required(VERSION 3.24)
project(02322Projekt2_Yukon C)

set(CMAKE_C_STANDARD 11)

include_directories(Controllers)
include_directories(Models)
include_directories(Views)

add_executable(02322Projekt2_Yukon
        Controllers/Filereader.c
        Controllers/Filereader.h
        Models/card.c
        Views/BoardView.c
        Views/BoardView.h)
