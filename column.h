//
// Created by asbpo on 14-04-2023.
//

#ifndef INC_02322PROJEKT2_YUKON_COLUMN_H
#define INC_02322PROJEKT2_YUKON_COLUMN_H
#include "deck.h"


typedef struct {
    int size;
    Card *head;
    Card *tail;
} Column;

void appendCard(Column **pColumn, Card **pCard);

void moveCard(Column **From, Column **To, char faceVal);

#endif //INC_02322PROJEKT2_YUKON_COLUMN_H
