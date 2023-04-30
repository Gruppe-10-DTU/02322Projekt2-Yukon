//
// Created by asbpo on 14-04-2023.
//
#include "filehandler.h"
#include "deck.h"
#include "board.h"
#include "board.h"
#include "column.h"
#include "stdio.h"
#include "string.h"
#include "command.h"
#include <unistd.h>

int hasWon(Board *board){
    int size = 0;
    for (int i = 0; i < 4; ++i) {
        size += board->foundation[i].size;
    }
    if(size == 52)
        return 1;
    else
        return 0;
}

/**
 *
 * @param board Board the game is started on
 * @author Asbjørn Nielsen, Nilas Thørgsen.
 */
void startGame(Board* board) {
    Command *cmd = NULL;
    char *moveCmd = NULL;
    char *lastMove = (char *) malloc(sizeof moveCmd);
    char *status = (char *) malloc(sizeof status);
    lastMove = NULL;
    status = "OK";
    while (hasWon(board) != 1) {
        moveCmd = NULL;
        printBoard(board);
        setbuf(stdout, 0);
        printGameConsole(lastMove, status);

        scanf("%ms", &moveCmd);
        if (strcmp(moveCmd, "Q") == 0) {
            printf("%s", "Exiting game...");
            break;
        }

        if (moveCmd[2] == ':' || moveCmd[2] == '-' || strcmp(moveCmd,"UNDO") == 0 || strcmp(moveCmd,"REDO") == 0) {
            cmd = playCommand(board, moveCmd);
            int doable = doCommand(board, cmd);
            if (doable == 1) {
                lastMove = moveCmd;
                status = "OK";
            } else if (doable == 0) {
                status = "Invalid Move";
            }
        }else {
            status = "Invalid Move";
            clearView();
            printWin();
        }
    }
    free(lastMove);
    free(moveCmd);
    free(status);
    free(cmd);
    clearView();
    if (hasWon(board) == 1) {
        printWin();
        usleep(2000000);
    }
}

int main() {
    char *cmd = NULL;
    //Initial Setup
    clearView();
    printTitle();

    //Reader

    //Nyt deck
    Card *deck = newDeck();
    shuffle(&deck);

    Board *board = createBoard();
    while (1) {
        clearView();
        printTitle();
        scanf("%ms", &cmd);
        if(strcmp(cmd,"P") == 0){
            loadDeck(board,deck);
            startGame(board);
        }
        else if(strcmp(cmd,"LD") == 0){
            scanf("Enter filename: %s", cmd);
            deck = deckFromFile(cmd);
            loadDeck(board,deck);
            printBoard(board);
        }
        else if(strcmp(cmd,"SW") == 0){

        }
        else if(strcmp(cmd,"SI") == 0){

        }
        else if(strcmp(cmd,"SR") == 0){

        }
        else if(strcmp(cmd,"SD") == 0){

        }
        else if(strcmp(cmd,"QQ") == 0){
            printf("%s","Exiting game. Goodbye!");
            break;

        }else{
            //TO BE IMPLEMENTED (Return error status).
        }
    }
    free(cmd);
    free(board);
    free(deck);
    return 0;
}