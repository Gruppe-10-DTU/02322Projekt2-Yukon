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
 *
 * @param str The string (with an integer) we want to convert to an integer.
 * @return returns the integer value int the string.
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
/**
 *
 * @param board The board we are undoing the command form
 * @param com The command we want to undo
 *
 * @author Asbjørn Nielsen, Nilas Thørgsen
 */
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
 * @author Asbjørn Nielsen, Nilas Thørgsen
 */
Command *playCommand(Board *board,char *str){
    char *tmp = strdup(str);
    char *from;
    char *card = (char*) malloc(sizeof strlen(tmp)+2);
    char *to;
    if(str[2] ==':'){
        from = strtok(tmp, ":");
        card = strtok(NULL,"-");
        to = strtok(NULL, ">");
    }
    else if(str[2] == '-') {
        from = strtok(tmp, "-");
        to = strtok(NULL, ">");
        int cToSelect = convertToDigit(str)-1;
        if(board->column[cToSelect].size < 1){
            return NULL;
        }
        if ((from[0] == 'C') && cToSelect > -1){
            char tmp1 = board->column[cToSelect].head->order;
            char tmp2 = board->column[cToSelect].head->suit;
            card[0] = tmp1;
            card[1] = tmp2;
            card[3] = '\0';

        }else if(from[0] == 'F' && cToSelect > -1 && cToSelect < 4) {
            to = &board->foundation[cToSelect].head->order;
            from = &board->foundation[cToSelect].head->suit;
            char tmp1 = board->foundation[cToSelect].head->order;
            char tmp2 = board->foundation[cToSelect].head->suit;
            card[0] = tmp1;
            card[1] = tmp2;
            card[2] = '\0';
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

    int from = convertToDigit(com->moveFrom)-1;
    int to = convertToDigit(com->moveTo)-1;

    if(isdigit(to) == 0 && isdigit(from) == 0) {
        if (com->moveFrom[0] == 'F' && from < 4 && to < 7) {
            if(findCard(board->column[from].head,com->card[1],com->card[0]) != NULL){
                Card *cardToFind = findCard(board->column[from].head,com->card[1],com->card[0]);
                if (moveIsValid(findCard(board->foundation[from].head, com->card[1], com->card[0]),
                                &board->column[to], 0) == 1 && cardToFind != NULL) {
                    moveCard(&board->foundation[from], &board->column[to],
                             cardToFind);
                    toReturn = 1;
                }
            }
        } else if(from < 7) {
            if (com->moveTo[0] == 'C' && board->column[from].head != NULL && to < 7) {
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
            } else if (com->moveTo[0] == 'F' && board->column[from].head != NULL && to < 4) {
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

void freeCommandList(Command *head){
    Command *tmp;
    while (head != NULL){
        tmp = head->nextCommand;
        free(head);
        head = tmp;
    }
}