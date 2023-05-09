//
// Created by pcramer on 4/24/23.
//
#include<stdlib.h>
#include<stdio.h>
#include "column-test.h"
#include "board-test.h"

int main(){

    printf("Column test exit code %d\n", columnTest());
    printf("Board test exit code %d\n", testBoard());
    printf("============================ BOARD TEST PRINT ============================\n");
    testPrintBoard();
    testPrintGameConsole();
    printf("\n============================ BOARD TEST PRINT ============================\n");
    char *status = (char *) calloc(1024,sizeof(char));
    deckFromFile("TEST-files/invalidDeckTooManyCards.txt", status);
    printf("%s\r\n", status);
    deckFromFile("TEST-files/invalidDeckDublicateCards.txt", status);
    printf("%s\r\n", status);
    return 0;
}