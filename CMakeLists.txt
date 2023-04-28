cmake_minimum_required(VERSION 3.17)
project(02322Projekt2_Yukon C)

set(CMAKE_C_STANDARD 23)

set(Headers
        deck.h
        board.h
        column.h
        filehandler.h)
set(Sources
        board.c
        column.c
        filehandler.c
        deck.c)
add_executable(02322Projekt2-Yukon main.c ${Sources} ${Headers})


set(Test_Source_Files
        TEST-files/main-test.c
        TEST-files/column-test.c
        ${Sources} TEST-files/board-test.c)
set(Test_Headers
        TEST-files/column-test.h TEST-files/board-test.c TEST-files/board-test.h command.c)
add_executable(Yukon_Test ${Test_Source_Files} ${Headers} ${Test_Headers})