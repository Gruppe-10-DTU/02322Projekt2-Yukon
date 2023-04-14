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

#endif //INC_02322PROJEKT2_YUKON_FILEHANDLER_H
