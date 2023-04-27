//
// Created by pcramer on 4/24/23.
//
#include<stdlib.h>
#include<stdio.h>
#include "column-test.h"
#include "board-test.h"

int main(){

    printf("Column test result: %d\n", columnTest());
    printf("============================= BOARD TEST TOP =============================\n");
    testPrintboard();
    testPrintGameConsole();
    printf("\n============================= BOARD TEST END =============================\n");

    return 0;
}