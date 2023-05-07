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


int convertToDigit(char *str){
    int toReturn = 0;
    char *tmp = strdup(str);
    while (*tmp && !isdigit(*tmp))
        ++tmp;
    toReturn = atoi(tmp);
    return toReturn;
}
void undoCommand(Board *board, Command *com){
    if(com == NULL){
        return;
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
            moveCard(&board->column[toDigit], &board->column[fromDigit], cardToUndo);
        } else if (moveTo[0] == 'F') {
            Card *cardToUndo = findCard(board->foundation[toDigit].head,card[1],card[0]);
            moveCard(&board->foundation[toDigit], &board->column[fromDigit], cardToUndo);
        }
    }
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
    char *tmp = strdup(str);
    char *from;
    char *card;
    char *to;
    if(str[2] ==':'){
        from = strtok(tmp, ":");
        card = strtok(NULL,"-");
        to = strtok(NULL, ">");
    }
    else if(str[2] == '-') {
        from = strtok(tmp, "-");

        int cToSelect = convertToDigit(str)-1;
        if(board->column[cToSelect].size < 1){
            return NULL;
        }
        if ((from[0] == 'C' || from[0] == 'F') && cToSelect > -1){
            to = &board->column[cToSelect].head->order;
            from = &board->column[cToSelect].head->suit;
            card = '\0';
        }else if(from[0] == 'F' && cToSelect > -1) {
            to = &board->foundation[cToSelect].head->order;
            from = &board->foundation[cToSelect].head->suit;
            card = '\0';
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
    Command *cmd = (Command *) malloc(sizeof(Command));
    cmd->nextCommand = NULL;
    cmd->prevCommand = NULL;
    cmd->moveTo = to;
    cmd->moveFrom = from;
    cmd->card = card;
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