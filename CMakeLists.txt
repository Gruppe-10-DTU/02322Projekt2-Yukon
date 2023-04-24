cmake_minimum_required(VERSION 3.24)
project(02322Projekt2_Yukon C)

set(CMAKE_C_STANDARD 23)

set(Headers
        deck.h
        board.h
        column.h
        filehandler.h)
set(Sources
        main.c
        board.c
        column.c
        filehandler.c
        deck.c)

add_executable(02322Projekt2-Yukon ${Sources} ${Headers})


set(Test_Source_Files TEST-files/main-test.c TEST-files/column-test.c deck.c column.c)
set(Test_Headers TEST-files/column-test.h)
add_executable(Yukon_Test ${Test_Source_Files} ${Headers} ${Test_Headers})