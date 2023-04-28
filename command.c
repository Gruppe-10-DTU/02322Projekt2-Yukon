//
// Created by asbpo on 28-04-2023.
//


#include <malloc.h>
#include "command.h"

void doCommand(char *moveTo, char *moveFrom, char *card){
    command *cmd;
    cmd = (char*) malloc(sizeof cmd);
    cmd->moveTo = moveTo;
    cmd->moveFrom = moveFrom;
    cmd->card = card;
    cmd->nextCommand = NULL;
    cmd->prevCommand = NULL;
};


