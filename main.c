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
    char *statusMsg = (char *) calloc(100, sizeof(char));
    //Initial Setup
    clearView();
    printTitle();

    //Reader

    //Nyt deck
    Card *deck = deckFromFile("new.txt", statusMsg);
    shuffle(&deck);
    int counter = 0;
    Card *tmp;
    while (deck != NULL && counter < 60){
        tmp = deck->nextCard;
        //printf("%c%c \r\n", tmp->order, tmp->suit);
        deck = tmp;
        counter++;
    }
    printf("%d", counter);
    Board *board = createBoard();

    while (1) {
        strcpy(statusMsg,"");
        scanf("%s", cmd);
        char *split = strtok(cmd, "<");
        cmdS1 = split;
        split = strtok("<",cmd);
        cmdS2 = split;
        if(strcmp(cmdS1,"P") == 0){
            startGame(board);
        }
        else if(strcmp(cmdS1,"LD") == 0){
            deck = deckFromFile(cmdS2,statusMsg);
            loadDeck(board,deck);
            printBoard(board);
            printGameConsole(cmd,statusMsg);
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
            strcpy(statusMsg, "Unknown command. See read me for available commands.");
            //TO BE IMPLEMENTED (Return error status).
        }
        clearView();
        printBoard(board);
        printGameConsole(cmd,statusMsg);
    }
    free(cmd);
    free(cmdS1);
    free(cmdS2);
    free(statusMsg);
    clearBoard(board);
    free(board);
    freeDeck(deck);
    return 0;
}