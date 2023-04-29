//
// Created by asbpo on 28-04-2023.
//


#include <malloc.h>
#include "command.h"
#include "column.h"
#include "stdio.h"
#include "string.h"
#include "board.h"


void doCommand(char *moveTo, char *moveFrom, char *card){
    command *cmd;
    cmd = (char*) malloc(sizeof cmd);
    cmd->moveTo = moveTo;
    cmd->moveFrom = moveFrom;
    cmd->card = card;
    cmd->nextCommand = NULL;
    cmd->prevCommand = NULL;
};

void playCommand(Board *board,char *str){
    char *tmp = strdup(str);
    if(strcmp(&str[2],":") == 0) {
        char *coulFro = strtok(tmp, ":");
        char *card = strtok(NULL,":");
        char *coulTo = strtok(NULL, "");
        doCommand(coulTo, coulFro, card);
        free(tmp);
    }
    else if(strcmp(&str[2], "-") == 0){
        char *coulFro = strtok(tmp,"-");
        char *coulTo = strtok(NULL,"-");
        char *card = NULL;
        for(int i = 0; i < board->column; i++){
            if(coulFro[1] == i) {
                char *tmp1 = &board->column[i].tail->order;
                char *tmp2 = &board->column[i].tail->suit;
                strcat(card,tmp1);
                strcat(card,tmp2);
                break;
            }
        }
        doCommand(coulTo,coulFro,card);
        }
    else if(strcmp(str,"UNDO") == 0 || strcmp(str,"undo") == 0){
        //Should return NULL for now.
    }else if(strcmp(str, "REDO") == 0 || strcmp(str,"redo") == 0){
        //Should return NULL for now.
    }else{
        //Should return NULL has it is not a valid command
    }
}
