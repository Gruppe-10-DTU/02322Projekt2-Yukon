//
// Created by asbpo on 28-04-2023.
//

#include "board.h"

#ifndef INC_02322PROJEKT2_YUKON_COMMAND_H
#define INC_02322PROJEKT2_YUKON_COMMAND_H

#endif //INC_02322PROJEKT2_YUKON_COMMAND_H


typedef struct command{
    char *moveFrom;
    char *moveTo;
    char *card;

    struct command *prevCommand;
    struct command *nextCommand;
}Command;



Command *playCommand(Board *board,char *str);
void undoCommand(Board *board, Command *com);
int doCommand(Board *board, Command *com);