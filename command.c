//
// Created by asbpo on 28-04-2023.
//


#include <malloc.h>
#include "command.h"
#include "column.h"
#include "string.h"
#include "board.h"
#include <ctype.h>

void addCommand(Command **head, char *moveTo, char *moveFrom, char *card){
    Command *cmd = (Command *) malloc(sizeof(Command));
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

Command *playCommand(Board *board,char *str){
    Command *cmd = NULL;
    char *tmp = strdup(str);
    if(str[2] ==':'){
        char *from = strtok(tmp, ":");
        char *card = strtok(NULL,"-");
        char *to = strtok(NULL, ">");
        addCommand(&cmd, to, from, card);

    }
    else if(str[2] == '-') {
        char *from = strtok(tmp, "-");
        char *to = strtok(NULL, ">");
        char *card = (char*) malloc(sizeof strlen(tmp)+2);
        if (from[0] == 'C') {
            char *tempCheck = strdup(from);
            while (*tempCheck && !isdigit(*tempCheck))
                ++tempCheck;
            if(*tempCheck) {
                char tmp1 = board->column[atoi(tempCheck)-1].head->order;
                char tmp2 = board->column[atoi(tempCheck)-1].head->suit;
                card[0] = tmp1;
                card[1] = tmp2;
                card[2] = '\0';
            }
        } else {
            if (from[0] == 'F') {
                char *tempCheck = strdup(from);
                while (*tempCheck && !isdigit(*tempCheck))
                    ++tempCheck;
                if(*tempCheck) {
                    char tmp1 = board->foundation[atoi(tempCheck)-1].head->order;
                    char tmp2 = board->foundation[atoi(tempCheck)-1].head->suit;
                    card[0] = tmp1;
                    card[1] = tmp2;
                    card[2] = '\0';
                }
            }
        }
        addCommand(&cmd, to, from, card);
    }else if(strcmp(str,"UNDO") == 0 || strcmp(str,"undo") == 0){

    }else if(strcmp(str, "REDO") == 0 || strcmp(str,"redo") == 0){

    }
    return cmd;
}


int doCommand(Board *board, Command *com, char fromForC, char toForC) {
    int toReturn = 0;
    char *fromDigit = strdup(com->moveFrom);
    while (*fromDigit && !isdigit(*fromDigit))
        ++fromDigit;
    char *toDigit = strdup(com->moveTo);
    while(*toDigit && !isdigit(*toDigit))
        ++toDigit;
    if (fromForC == 'F') {
        if (moveIsValid(findCard(board->foundation[atoi(fromDigit)-1].head, com->card[1], com->card[0]),
                        &board->column[atoi(toDigit)-1], 0) == 1) {
            moveCard(&board->foundation[atoi(fromDigit)-1], &board->column[(int) com->moveTo[1]],
                     findCard(board->foundation->head, com->card[1], com->card[0]));
            toReturn = 1;
        }
    }else{
        if(toForC == 'C'){
            if (moveIsValid(
                    findCard(board->column[atoi(fromDigit)-1].head, com->card[1], com->card[0]),
                    &board->column[atoi(toDigit)-1], 0) == 1) {
                moveCard(&board->column[atoi(fromDigit)-1], &board->column[(int) com->moveTo[1]],
                         findCard(board->column[atoi(fromDigit)-1].head, com->card[1], com->card[0]));
                toReturn = 1;
            }
        }else if(toForC == 'F'){
            if (moveIsValid(
                    findCard(board->column[atoi(fromDigit) - 1].head, com->card[1], com->card[0]),
                    &board->foundation[atoi(toDigit)-1],1) == 1) {
                moveCard(&board->column[atoi(fromDigit)-1], &board->foundation[atoi(toDigit)-1],
                         findCard(board->column[atoi(fromDigit)-1].head, com->card[1], com->card[0]));
                toReturn = 1;
            }
        }
    }
    return toReturn;
}