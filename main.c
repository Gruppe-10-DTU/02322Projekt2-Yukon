//
// Created by asbpo on 14-04-2023.
//
#include "filehandler.h"
#include "deck.h"
#include "board.h"


void startGame(Board* board, char *statusMsg){
    char cmd[4] = {0};
    while (!gameFinished(board)){
        if(strcasecmp("Q", cmd) == 0){
            strcpy(statusMsg, "Quitting game.");
            clearBoard(board);
            return;
        } else if (!strcasecmp(cmd,"LD") || !strcasecmp(cmd,"SW") || !strcasecmp(cmd,"SR") ||
            !strcasecmp(cmd,"SI") || !strcasecmp(cmd,"SD")){
            strcpy(statusMsg, "Command not available in the PLAY phase");
        }
        clearView();
        printBoard(board);
        printGameConsole(cmd,statusMsg);
    }
    //DOES NOTHING FOR NOW WIP.
}


int main() {
    char *cmd = NULL;//(char *) calloc(100,sizeof(cmd));
    char *cmdS1 = (char *) malloc(sizeof cmdS1);
    char *cmdS2 = (char *) malloc(sizeof cmdS2);
    char *statusMsg = (char *) calloc(100, sizeof(char));
    //Initial Setup
    clearView();
    printTitle();

    //Reader

    //Nyt deck
    Card *deck = NULL;
    Board *board = createBoard();

    while (1) {
        strcpy(statusMsg,"");
        scanf("%ms", &cmd);
        char *split = strtok(cmd, "<");
        cmdS1 = split;
        split = strtok(NULL,">");
        cmdS2 = split;
        //printf("Command: %s\nArgument: %s\n", cmdS1, cmdS2);
        if(strcasecmp(cmdS1,"P") == 0){
            clearView();
            if(deck) {
                shuffle(&deck);
                loadDeck(board, deck);
                printBoard(board);
                printGameConsole(cmdS1, "Game Started");
                startGame(board, statusMsg);
            }else {
                printBoard(board);
                printGameConsole(cmdS1, "No deck loaded.");
            }
        }
        else if(strcasecmp(cmdS1,"LD") == 0){
            if (cmdS2) {
                deck = deckFromFile(cmdS2,statusMsg);
            } else deck = newDeck(statusMsg);
            clearView();
            showDeck(board, deck, 0);
            printGameConsole(cmdS1,statusMsg);
        }
        else if(strcasecmp(cmdS1,"SW") == 0){
            clearView();
            showDeck(board, deck, 1);
            printGameConsole(cmdS1,"OK");
        }
        else if(strcasecmp(cmdS1,"SI") == 0){
            clearView();
            printBoard(board);
            printGameConsole(cmdS1,"OK");
        }
        else if(strcasecmp(cmdS1,"SR") == 0){
            clearView();
            shuffle(&deck);
            printBoard(board);
            printGameConsole(cmdS1,"OK");
        }
        else if(strcasecmp(cmdS1,"SD") == 0){
            clearView();
            printBoard(board);
            printGameConsole(cmdS1,"OK");
        }
        else if(strcasecmp(cmdS1,"QQ") == 0){
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