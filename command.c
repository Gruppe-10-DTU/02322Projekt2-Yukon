//
// Created by asbpo on 28-04-2023.
//


#include <malloc.h>
#include "command.h"
#include "column.h"
#include "string.h"
#include "board.h"
#include <ctype.h>
/**
 * Command cards in a linked-list structure.
 * @param head Head of commands
 * @param moveTo Where the commands moves the card to
 * @param moveFrom Where the commands moves the cards from
 * @param card Suit and order of card we wish to move.
 *
 * @author Asbjørn Nielsen
 */
void addCommand(Command **head, char *moveTo, char *moveFrom, char *card){
    Command *cmd = (Command *) malloc(sizeof(Command));
    cmd->moveTo = moveTo;
    cmd->moveFrom = moveFrom;
    cmd->card = card;
    if (*head == NULL){
        *head = cmd;
        cmd->nextCommand = NULL;
    } else{
        cmd->nextCommand = *head;
        (*head)->prevCommand = cmd;
        *head = cmd;
    }
};


int convertToDigit(char *str){
    int toReturn = 0;
    char *tmp = strdup(str);
    while (*tmp && !isdigit(*tmp))
        ++tmp;
    toReturn = atoi(tmp);
    return toReturn;
}
Command *undoCommand(Board *board, Command *com){
    if(com == NULL || com->prevCommand == NULL){
        return NULL;
    }
    char *moveFrom = com->moveFrom;
    char *moveTo = com->moveTo;
    char *card = com->card;
    int fromDigit = convertToDigit(moveFrom) - 1;
    int toDigit = convertToDigit(moveTo) - 1;
    if (moveFrom[0] == 'F') {
        Card *cardToFind = board->column[fromDigit].head;
        moveCard(&board->column[toDigit], &board->column[fromDigit], cardToFind);
    } else {
        if (moveTo[0] == 'C') {
            Card *cardToUndo = findCard(board->column[toDigit].head, card[1], card[0]);
            moveCard(&board->column[fromDigit], &board->column[toDigit], cardToUndo);
        } else if (moveTo[0] == 'F') {
            Card *cardToUndo = findCard(board->foundation[toDigit].head,card[1],card[0]);
            moveCard(&board->foundation[fromDigit], &board->column[toDigit], cardToUndo);
        }
    }
    return com->prevCommand;
}
/**
 *
 * @param board The board we are playing the command on
 * @param str The loaded moveCmd string.
 * @return returns the reference to the command.
 *
 * @author Asbjørn Nielsen
 */
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
        int cToSelect = convertToDigit(str)-1;
        if(board->column[cToSelect].size < 1){
            return cmd;
        }
        if ((from[0] == 'C' || from[0] == 'F') && cToSelect > -1){
            char tmp1 = board->column[cToSelect].head->order;
            char tmp2 = board->column[cToSelect].head->suit;
            card[0] = tmp1;
            card[1] = tmp2;
            card[2] = '\0';
            addCommand(&cmd, to, from, card);

        }else if(from[0] == 'F' && cToSelect > -1) {
            char tmp1 = board->foundation[cToSelect].head->order;
            char tmp2 = board->foundation[cToSelect].head->suit;
            card[0] = tmp1;
            card[1] = tmp2;
            card[2] = '\0';
            addCommand(&cmd, to, from, card);
        }else{

        }
    }
    return cmd;
}



/**
 *
 * @param board Board the command should be execute on.
 * @param com The command
 * @return returns 1 if doable, otherwise returns 0.
 *
 * @author Asbjørn Nielsen
 */
int doCommand(Board *board, Command *com) {
    int toReturn = 0;
    if(!com){
        return toReturn;
    }
    char *fromDigit = strdup(com->moveFrom);
    while (*fromDigit && !isdigit(*fromDigit))
        ++fromDigit;
    char *toDigit = strdup(com->moveTo);
    while(*toDigit && !isdigit(*toDigit))
        ++toDigit;

    int to = atoi(toDigit)-1;
    int from = atoi(fromDigit)-1;
    if(isdigit(to) == 0 && isdigit(from) == 0) {
        if (com->moveFrom[0] == 'F') {
            if(findCard(board->column[from].head,com->card[1],com->card[0]) != NULL){
                Card *cardToFind = findCard(board->column[from].head,com->card[1],com->card[0]);
                if (moveIsValid(findCard(board->foundation[from].head, com->card[1], com->card[0]),
                                &board->column[to], 0) == 1 && cardToFind != NULL) {
                    moveCard(&board->foundation[from], &board->column[to],
                             cardToFind);
                    toReturn = 1;
                }
            }
        } else {
            if (com->moveTo[0] == 'C' && board->column[from].head != NULL) {
                if (findCard(board->column[from].head, com->card[1], com->card[0]) != NULL){
                    Card *cardToFind = findCard(board->column[from].head, com->card[1], com->card[0]);
                    if (moveIsValid(
                            findCard(board->column[from].head, com->card[1], com->card[0]),
                            &board->column[to], 0) == 1 && cardToFind != NULL) {
                        moveCard(&board->column[from], &board->column[to],
                                 cardToFind);
                        toReturn = 1;
                    }
                }
            } else if (com->moveTo[0] == 'F' && board->column[from].head != NULL) {
                if (findCard(board->column[from].head, com->card[1], com->card[0]) != NULL){
                    Card *cardToFind = findCard(board->column[from].head, com->card[1], com->card[0]);
                    if (moveIsValid(
                            findCard(board->column[from].head, com->card[1], com->card[0]),
                            &board->foundation[to], 1) == 1 && cardToFind != NULL) {
                        moveCard(&board->column[from], &board->foundation[to],
                                 cardToFind);
                        toReturn = 1;
                    }
                }
            }
        }
    }
    return toReturn;
}