//
// Created by asbpo on 14-04-2023.
//
#include "filehandler.h"
#include "deck.h"
#include "board.h"


void startGame(Board* board){
    //DOES NOTHING FOR NOW WIP.
}


int main() {
    char *cmd = (char *) calloc(100,sizeof(cmd));
    char *cmdS1 = (char * ) malloc(sizeof cmdS1);
    char *cmdS2 = (char*) malloc(sizeof cmdS2);
    char *statusMsg = (char *) calloc(100, sizeof(char));
    //Initial Setup
    clearView();
    printTitle();

    //Reader

    //Nyt deck
    Card *deck = newDeck(statusMsg);

    Board *board = createBoard();

    while (1) {
        strcpy(statusMsg,"");
        scanf("%s", cmd);
        char *split = strtok(cmd, "<");
        cmdS1 = split;
        split = strtok("<",cmd);
        cmdS2 = split;
        if(strcmp(cmdS1,"P") == 0){
            loadDeck(board,deck);
            startGame(board);
        }
        else if(strcmp(cmdS1,"LD") == 0){
            deck = deckFromFile(cmdS2,statusMsg);
            clearView();
            showDeck(board, deck, 0);
            printGameConsole(cmdS1,statusMsg);
        }
        else if(strcmp(cmdS1,"SW") == 0){
            clearView();
            showDeck(board, deck, 1);
            printGameConsole(cmdS1,"OK");
        }
        else if(strcmp(cmdS1,"SI") == 0){
            clearView();
            printBoard(board);
            printGameConsole(cmdS1,"OK");
        }
        else if(strcmp(cmdS1,"SR") == 0){
            clearView();
            shuffle(&deck);
            printBoard(board);
            printGameConsole(cmdS1,"OK");
        }
        else if(strcmp(cmdS1,"SD") == 0){
            clearView();
            printBoard(board);
            printGameConsole(cmdS1,"OK");
        }
        else if(strcmp(cmdS1,"QQ") == 0){
            strcpy(statusMsg, "Thank you for playing!");
            clearView();
            clearBoard(board);
            printBoard(board);
            printGameConsole(cmd,statusMsg);
            break;
        }else{
            strcpy(statusMsg, "Unknown command. See read me for available commands.");
            clearView();
            printBoard(board);
            printGameConsole(cmd,statusMsg);
            //TO BE IMPLEMENTED (Return error status).
        }
    }
    free(cmdS1);
    //free(cmdS2);
    freeDeck(deck);
    free(statusMsg);
    free(board);
    return 0;
}