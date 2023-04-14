//
// Created by asbpo on 14-04-2023.
//

#ifndef INC_02322PROJEKT2_YUKON_DECK_H
#define INC_02322PROJEKT2_YUKON_DECK_H

#include<stdlib.h>

typedef struct card{
    char order;
    char suit;
    int visible;
    struct card *nextCard;
    struct card *prevCard;
}Card;

void addCard(Card **head, char suit, char order);

#endif //INC_02322PROJEKT2_YUKON_DECK_H
