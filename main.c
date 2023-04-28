//
// Created by asbpo on 14-04-2023.
//
#include "filehandler.h"
#include "deck.h"
#include "board.h"
#include "board.h"
#include "column.h"
#include "stdio.h"


void startGame(Board* board){
    //DOES NOTHING FOR NOW WIP.
}


int main() {
    char *cmd = (char *) malloc(sizeof(cmd));
    char *cmdS1 = (char * ) malloc(sizeof cmdS1);
    char *cmdS2 = (char*) malloc(sizeof cmdS2);
    //Initial Setup
    clearView();
    printTitle();
    Board *board = createBoard();
    Card *deck = newDeck();

    while (1) {
        printTitle();
        scanf("%s", cmd);
        char *split = strtok(cmd, "<");
        cmdS1 = split;
        split = strtok("<",cmd);
        cmdS2 = split;
        if(strcmp(cmdS1,"P") == 0){
            startGame(board);
        }
        else if(strcmp(cmdS1,"LD") == 0){
            deck = deckFromFile(cmdS2);
            loadDeck(board,deck);
            printBoard(board);
        }
        else if(strcmp(cmdS1,"SW") == 0){

        }
        else if(strcmp(cmdS1,"SI") == 0){

        }
        else if(strcmp(cmdS1,"SR") == 0){

        }
        else if(strcmp(cmdS1,"SD") == 0){

        }
        else if(strcmp(cmdS1,"QQ") == 0){
            break;
        }else{
            //TO BE IMPLEMENTED (Return error status).
        }
    }
    free(cmd);
    free(cmdS1);
    free(cmdS2);
    return 0;
}
