//
// Created by asbpo on 14-04-2023.
//
#include "filehandler.h"
#include "deck.h"
#include "board.h"
#include "stdio.h"
#include "string.h"
#include "command.h"


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
        //Used for debug only. Wouldn't print console output when debugging, found this solution online.
        setbuf(stdout, 0);
        printGameConsole(lastMove, status);
        scanf("%ms", &moveCmd);
        if (strcmp(moveCmd, "Q") == 0) {
            printf("%s", "Exiting game...");
            break;
        }
        //Check to see if the input is one of the variants of valid commands.
        if (moveCmd[2] == ':' || moveCmd[2] == '-') {
            cmd = playCommand(board, moveCmd);
            int doable = doCommand(board, cmd);
            if (doable == 1) {
                lastMove = moveCmd;
                status = "OK";
            } else if (doable == 0) {
                status = "Invalid Move";
            }
        }else if(strcmp(moveCmd,"UNDO") == 0 || strcmp(moveCmd,"undo") == 0){
            undoCommand(board,cmd);
        }else {
            status = "Invalid Move";
            clearView();
        }
    }
    free(lastMove);
    free(moveCmd);
    free(status);
    free(cmd);
    clearView();
    if (hasWon(board) == 1) {
        printWin();
    }
}


int main() {
    char *statusMsg = (char *) calloc(100, sizeof(char));
    char *cmd = NULL;
    //Initial Setup
    clearView();
    printTitle();

    //Reader

    //Nyt deck
    Card *deck = newDeck("OK");
    shuffle(&deck);

    Board *board = createBoard();

    while(1) {
        clearView();
        printTitle();
        scanf("%ms", &cmd);
        if(strcmp(cmd,"P") == 0){
            loadDeck(board,deck);
            startGame(board);
        }
        else if(strcmp(cmd,"LD") == 0){
            scanf("Enter filename: %s", cmd);
            deck = deckFromFile(cmd,"OK");
            loadDeck(board,deck);
            printBoard(board);
        }
        else if(strcasecmp(cmd,"LD") == 0){
            if (cmd) {
                deck = deckFromFile(cmd,statusMsg);
            } else deck = newDeck(statusMsg);
            clearView();
            showDeck(board, deck, 0);
            printGameConsole(cmd,statusMsg);
        }
        else if(strcasecmp(cmd,"SW") == 0){
            clearView();
            showDeck(board, deck, 1);
            printGameConsole(cmd,"OK");
        }
        else if(strcasecmp(cmd,"SI") == 0){
            clearView();
            printBoard(board);
            printGameConsole(cmd,"OK");
        }
        else if(strcasecmp(cmd,"SR") == 0){
            clearView();
            shuffle(&deck);
            printBoard(board);
            printGameConsole(cmd,"OK");
        }
        else if(strcasecmp(cmd,"SD") == 0){
            clearView();
            printBoard(board);
            printGameConsole(cmd,"OK");
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
    free(deck);
    free(statusMsg);
    return 0;
}