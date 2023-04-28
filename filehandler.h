//
// Created by asbpo on 14-04-2023.
//

#ifndef INC_02322PROJEKT2_YUKON_FILEHANDLER_H
#define INC_02322PROJEKT2_YUKON_FILEHANDLER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deck.h"

Card *deckFromFile(char *filename);

Card *newDeck();

void saveCard(Card *card, FILE *file);

void saveDeck(Card *deck, char *filename);

int deckIsValid(Card *head, char suit, char order, int *counter);


#endif //INC_02322PROJEKT2_YUKON_FILEHANDLER_H
