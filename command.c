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
    Command *cmd = NULL;
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
        if(strcmp(&from[0],"C") == 0) {
            for (int i = 0; i < 7; i++) {
                if (from[1] == i) {
                    char *tmp1 = &board->column[i].tail->order;
                    char *tmp2 = &board->column[i].tail->suit;
                    strcat(card, tmp1);
                    strcat(card, tmp2);
                    free(tmp1);
                    free(tmp2);
                    break;
                }
            }
        }else {
            if(strcmp(&from[0], "F") == 0){
            for (int i = 0; i < 4; ++i) {
                if(from[1] == i){
                    char *tmp1 = &board->foundation[i].tail->order;
                    char *tmp2 = &board->foundation[i].tail->suit;
                    strcat(card,tmp2);
                    strcat(card,tmp1);
                    free(tmp1);
                    free(tmp2);
                    break;
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

int doCommand(Board *board, Command *com, char fromForC, char toForC) {
    int toReturn = 0;
    if (fromForC == 'F') {
        if (moveIsValid(findCard(board->foundation[(int) com->moveFrom[1]].head, com->card[0], com->card[1]),
                        &board->column[(int) com->moveTo[1]], 0) == 1) {
            moveCard(&board->foundation[(int) com->moveFrom[1]], &board->column[(int) com->moveTo[1]],
                     findCard(board->foundation->head, com->card[0], com->card[1]));
            toReturn = 1;
        }
    }else{
        if(toForC == 'C'){
            if (moveIsValid(
                    findCard(board->column[(int) com->moveFrom[1]].head, com->card[0], com->card[1]),
                    &board->column[(int) com->moveTo[1]], 0) == 1) {
                moveCard(&board->column[(int) com->moveFrom[1]], &board->column[(int) com->moveTo[1]],
                         findCard(board->column[(int) com->moveFrom[1]].head, com->card[0], com->card[1]));
                toReturn = 1;
            }
        }else if(toForC == 'F'){
            if (moveIsValid(
                    findCard(board->column[(int) com->moveFrom[1]].head, com->card[0], com->card[1]),
                    &board->foundation[(int) com->moveTo[1]],1) == 1) {
                moveCard(&board->column[(int) com->moveFrom[1]], &board->foundation[(int) com->moveTo[1]],
                         findCard(board->column[(int) com->moveFrom[1]].head, com->card[0], com->card[1]));
                toReturn = 1;
            }
        }
    }
    return toReturn;
}