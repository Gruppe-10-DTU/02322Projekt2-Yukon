//
// Created by asbpo on 28-04-2023.
//


#include <malloc.h>
#include "command.h"
#include "column.h"
#include "stdio.h"
#include "string.h"
#include "board.h"


void addCommand(Command **head, char *moveTo, char *moveFrom, char *card){
    Command *cmd;
    cmd = (char*) malloc(sizeof cmd);
    cmd->moveTo = moveTo;
    cmd->moveFrom = moveFrom;
    cmd->card = card;
    cmd->prevCommand = NULL;
    if (*head == NULL){
        *head = cmd;
        cmd->nextCommand = NULL;
    } else{
        cmd->nextCommand = *head;
        (*head)->prevCommand = cmd;
        *head = cmd;
    }
};

void playCommand(Board *board,char *str){
    Command *cmd = NULL;
    char *tmp = strdup(str);
    if(strcmp(&str[2],":") == 0) {
        char *from = strtok(tmp, ":");
        char *card = strtok(NULL,":");
        char *to = strtok(NULL, "");
        addCommand(&cmd, to, from, card);
        free(tmp);
    }
    else if(strcmp(&str[2], "-") == 0){
        char *from = strtok(tmp, "-");
        char *to = strtok(NULL, "-");
        char *card = NULL;
        if(strcmp(&from[0],"C")) {
            for (int i = 0; i < 7; i++) {
                if (from[1] == i) {
                    char *tmp1 = &board->column[i].tail->order;
                    char *tmp2 = &board->column[i].tail->suit;
                    strcat(card, tmp1);
                    strcat(card, tmp2);
                    break;
                }
            }
        }else {
            if(strcmp(&from[0], "F") == 0){
            for (int i = 0; i < 4; ++i) {
                if(from[1] == i){
                    char *tmp1 = &board->foundation[i].tail->order;
                    char *tmp2 = &board->foundation[i].tail->suit;
                    strcat(card,tmp1);
                    strcat(card,tmp2);
                }
            }
        }
        }
        addCommand(&cmd, to, from, card);
        }
    else if(strcmp(str,"UNDO") == 0 || strcmp(str,"undo") == 0){

    }else if(strcmp(str, "REDO") == 0 || strcmp(str,"redo") == 0){

    }else{
        //Should return NULL if it is not a valid Command
    }
}
