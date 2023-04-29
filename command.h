//
// Created by asbpo on 28-04-2023.
//

#include "board.h"

#ifndef INC_02322PROJEKT2_YUKON_COMMAND_H
#define INC_02322PROJEKT2_YUKON_COMMAND_H

#endif //INC_02322PROJEKT2_YUKON_COMMAND_H


typedef struct{
    char *moveFrom;
    char *moveTo;
    char *card;
    struct command *prevCommand;
    struct command *nextCommand;
}Command;


void playCommand(Board *board,char *str);

void addCommand(Command **head, char *moveTo, char *moveFrom, char *card);