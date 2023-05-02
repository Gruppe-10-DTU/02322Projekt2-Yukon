//
// Created by asbpo on 14-04-2023.
//

#ifndef INC_02322PROJEKT2_YUKON_BOARD_H
#define INC_02322PROJEKT2_YUKON_BOARD_H
#include<stdio.h>
#include "column.h"
#define COLUMNS 7
#define FOUNDATIONS 4
#define SUIT_SIZE 13

typedef struct {
    Column column[COLUMNS];
    Column foundation[FOUNDATIONS];
}Board;

Board *createBoard(void);
void loadDeck(Board *board, Card *deck);
void clearBoard(Board *board);
void printBoard(Board *board);
void printGameConsole(char *lastCommand, char *message);
void printTitle(void);
void clearView(void);
void showDeck(Board *board, Card *deck, int visible);
int gameFinished(Board *board);

#endif //INC_02322PROJEKT2_YUKON_BOARD_H
