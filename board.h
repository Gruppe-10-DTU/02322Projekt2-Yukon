//
// Created by asbpo on 14-04-2023.
//

#ifndef INC_02322PROJEKT2_YUKON_BOARD_H
#define INC_02322PROJEKT2_YUKON_BOARD_H
#include<stdio.h>
#include "column.h"

typedef struct {
    Column column[7];
    Column foundation[4];
}Board;

Board *createBoard();
void loadDeck(Board *board, Card *deck);
void clearBoard(Board *board);
void printBoard(Board *board);
void printGameConsole(char *lastCommand, char *message);
void printTitle();
void printWin();
void clearView();

#endif //INC_02322PROJEKT2_YUKON_BOARD_H
