//
// Created by pcramer on 4/26/23.
//

#include "board-test.h"

int testCreateBoard(){
    int result = 0;
    Board *board = createBoard();
    if(board == NULL) result++;
    free(board);
    return result;
}
int testLoadDeck(){
    int result = 0;
    Board *board = createBoard();
    char *statusMsg = (char *) calloc(35,sizeof(char));
    Card *deck = deckFromFile("new.txt", statusMsg);
    loadDeck(board, deck);
    int columnCount[7] = {1,6,7,8,9,10,11};
    for(int i = 0; i < 7; i++){
        if(board->column[i].size < columnCount[i]) {
            //printf("\nCOLUMN %d SIZE %d", i ,board->column[i].size);
            result++;
        }
    }
    free(board);
    freeDeck(deck);
    free(statusMsg);
    return result;
}
int testClearBoard(){
    int result = 0;
    char *statusMsg = (char *) calloc(35,sizeof(char));
    Board *board = createBoard();
    Card *deck = deckFromFile("new.txt", statusMsg);
    loadDeck(board, deck);
    clearBoard(board);
    for(int i = 0; i < 7; i++){
        if(board->column[i].size) result++;
    }
    free(board);
    free(statusMsg);
    return result;
}

void testPrintBoard() {
    //SETUP
    Board *board = createBoard();
    char *statusMsg = (char *) calloc(35,sizeof(char));
    Card *deck = deckFromFile("new.txt", statusMsg);
    loadDeck(board,deck);

    //TEST PRINT
    printBoard(board);

    //TEARDOWN
    clearBoard(board);
    printf("\n");
    printBoard(board);

    free(board);
    free(statusMsg);
}

void testPrintGameConsole(){
    char *statusMsg = (char *) calloc(35,sizeof(char));
    Card *deck = deckFromFile("new.txt", statusMsg);
    char *lastCommand = "LD";
    printGameConsole(lastCommand,statusMsg);

    freeDeck(deck);
    free(statusMsg);
}
int testBoard(){
    int result = 0;
    result += testCreateBoard();
    result += testLoadDeck() * 10;
    result += testClearBoard() * 100;
    return result;
}
