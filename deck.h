//
// Created by asbpo on 14-04-2023.
//

#ifndef INC_02322PROJEKT2_YUKON_DECK_H
#define INC_02322PROJEKT2_YUKON_DECK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct card{
    char order;
    char suit;
    int visible;
    struct card *nextCard;
    struct card *prevCard;
}Card;
void addCard(Card **head, char suit, char order);
Card* findCard(Card* cards, char suit, char order);

void freeDeck(Card *head);

int countDeck(Card *head);

void shuffle(Card **head);

void split(Card **head, int split);

#endif //INC_02322PROJEKT2_YUKON_DECK_H
