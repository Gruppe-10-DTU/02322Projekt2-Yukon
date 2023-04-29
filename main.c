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

void startGame(Board* board){
        Command *cmd = NULL;
        char *moveCmd = (char*)malloc(sizeof(moveCmd));
        char *lastMove = (char*) malloc(sizeof moveCmd);
        char *status = (char*) malloc(sizeof status);
        lastMove = NULL;
        status = "OK";
        while(hasWon(board) != 1){
            printBoard(board);
            printGameConsole(lastMove,status);
            scanf("%s",moveCmd);
            if(strcmp(moveCmd,"Q") == 0){
                printf("%s", "Exiting game...");
                break;
            }
            if(strcmp(&moveCmd[2],":") == 0 || strcmp(&moveCmd[2], "-") == 0){
                playCommand(board, moveCmd);
                int doable = doCommand(board,cmd,cmd->moveFrom[0],cmd->moveTo[0]);
                if(doable == 1){
                    lastMove = moveCmd;
                    status = "OK";
                }else if(doable == 0){
                    status = "ERROR";
                }
            }else{
                //Could do something here if we wanted to.
            }
        }
        usleep(2000000);
        free(moveCmd);
        free(lastMove);
        clearView();
        printWin();
        usleep(2000000);
}


int main() {
    char *cmd = (char *) malloc(sizeof(cmd));
    char *cmdS1 = (char * ) malloc(sizeof cmdS1);
    char *cmdS2 = (char*) malloc(sizeof cmdS2);
    //Initial Setup
    clearView();
    printTitle();

    //Reader

    //Nyt deck
    Card *deck = deckFromFile("new.txt");
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
        printTitle();
        scanf("%s", cmd);
        if(strcmp(cmd,"P") == 0){
            loadDeck(board,deck);
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