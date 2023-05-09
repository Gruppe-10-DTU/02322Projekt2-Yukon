//
// Created by asbpo on 14-04-2023.
//
#include "filehandler.h"
#include "deck.h"
#include "board.h"
#include "stdio.h"
#include "string.h"
#include "command.h"
#define INT_OFFSET 48


int parseInteger(char *s2) {
    int result = 0;
    int tmp = 0;
    for(int i = 0; s2[i]; i++){
        tmp = ((int) s2[i]) - INT_OFFSET;
        result *= 10;
        result += tmp;
    }
    return result;
}


/**
 *
 * @param board Board the game is started on
 * @author Asbjørn Nielsen, Nilas Thørgsen.
 */
void startGame(Board* board) {
    //Head of the cmd line
    Command *cmdHead = (Command*) malloc(sizeof(Command));
    Command *cmd = (Command*) malloc(sizeof (Command));

    char *moveCmd = NULL;
    char *lastMove = (char *) malloc(sizeof moveCmd);
    char *status = (char *) calloc(1024,sizeof(char));
    lastMove = NULL;
    strcpy(status, "OK");
    while (!gameFinished(board)) {
        moveCmd = NULL;
        printBoard(board);
        //Used for debug only. Wouldn't print console output when debugging, found this solution online.
        setbuf(stdout, 0);
        printGameConsole(lastMove, status);
        moveCmd = (char*) malloc(sizeof moveCmd);
        scanf("%s", moveCmd);
        if (strcasecmp(moveCmd, "Q") == 0) {
            strcpy(status, "Exiting game...");
            break;
        }
        //Check to see if the input is one of the variants of valid commands.
        if (moveCmd[2] == ':' || moveCmd[2] == '-') {
            //Create the command
            cmd = playCommand(board, moveCmd);

            int doable = doCommand(board, cmd);
            if (doable == 1) {
                lastMove = moveCmd;
                cmdHead->nextCommand = cmd;
                cmd->prevCommand = cmdHead;
                cmdHead = cmd;
                strcpy(status, "OK");
            } else if (doable == 0) {
                strcpy(status, "Invalid Move");
            }
        }else if(strcasecmp(moveCmd,"UNDO") == 0){
            if(cmdHead->prevCommand != NULL){
                undoCommand(board,cmdHead);
                cmdHead = cmdHead->prevCommand;
            }else{
                strcpy(status, "No move to undo");
            }
        }
        else if(strcasecmp(moveCmd,"REDO") == 0) {
            if (cmdHead->nextCommand != NULL) {
                doCommand(board, cmdHead);
                cmdHead = cmdHead->nextCommand;
            } else {
                strcpy(status, "No move to redo");
            }
        }else {
            strcpy(status, "Invalid Move");
            clearView();
        }
    }
    if (gameFinished(board)) {
        printWin();
    }
    clearView();
    clearBoard(board);
    printBoard(board);
    printGameConsole(lastMove,status);
    free(lastMove);
    free(moveCmd);
    free(status);
    freeCommandList(cmdHead);
    free(cmd);
    free(moveCmd);
    getchar();
}


int main() {
    char *statusMsg = (char *) calloc(100, sizeof(char));
    char *cmd = (char *) calloc(1024, sizeof(char));
    char *cmdS1 = NULL;
    char *cmdS2 = NULL;
    //Initial Setup
    clearView();
    printTitle();
    Board *board = createBoard();
    Card *deck = NULL;
    clearView();
    printTitle();
    while(1) {
        fgets(cmd, 1024,stdin);
        cmd = strtok(cmd, "\n");
        cmdS1 = strtok(cmd," ");
        cmdS2 = strtok(NULL,"\n");
        if(strcasecmp(cmd,"P") == 0){
            if(!deck){
                deck = newDeck(statusMsg);
                shuffle(&deck);
            }
            loadDeck(board,deck);
            deck = NULL;
            startGame(board);
        }
        else if(strcasecmp(cmd,"LD") == 0){
            clearView();
            if (deck) freeDeck(deck);
            if (cmdS2) {
                deck = deckFromFile(cmdS2,statusMsg);
            } else deck = newDeck(statusMsg);
            if (deck) {
                showDeck(board, deck, 0);
            } else {
                printBoard(board);
            }
            printGameConsole(cmd,statusMsg);
        }
        else if(strcasecmp(cmd,"SW") == 0){
            clearView();
            showDeck(board, deck, 1);
            printGameConsole(cmd,"OK");
        }
        else if(strcasecmp(cmd,"SI") == 0){
            clearView();
            if(cmdS2) {
                int splitIndex = parseInteger(cmdS2);
                split(&deck, splitIndex);
            }else split(&deck,2);
            printBoard(board);
            printGameConsole(cmd,"OK");
        }
        else if(strcasecmp(cmd,"SR") == 0){
            clearView();
            shuffle(&deck);
            showDeck(board, deck, 0);
            printGameConsole(cmd,"OK");
        }
        else if(strcasecmp(cmd,"SD") == 0){
            if(cmdS2 != NULL){
                saveDeck(deck, cmdS2);
                clearView();
                printGameConsole(cmd,"OK");
            }else{
                printGameConsole(cmd,"Filename needs to be written");
            }
        }
        else if(strcasecmp(cmd,"QQ") == 0){
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
        }
    }
    free(cmd);
    free(board);
    if(deck) freeDeck(deck);
    free(statusMsg);
    return 0;
}
