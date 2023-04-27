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
    Card *deck = deckFromFile("../new.txt");
    loadDeck(board, deck);
    for(int i = 0; i < 7; i++){
        if(board->column[i].size < 1) {
            printf("\nCOLUMN %d SIZE %d", i ,board->column[i].size);
            result++;
        }
    }
    for(int j = 0; j < 7; j++){
        while(board->column[j].head != NULL){
            Card *tmp = board->column[j].head->nextCard;
            free(board->column[j].head);
            board->column[j].head = tmp;
        }
    }
    free(board);
    return result;
}
int testClearBoard(){
    int result = 0;
    Board *board = createBoard();
    Card *deck = deckFromFile("../new.txt");
    loadDeck(board, deck);
    clearBoard(board);
    for(int i = 0; i < 7; i++){
        if(board->column[i].size) result++;
    }
    free(board);
    return result;
}

void testPrintBoard() {
    //SETUP
    Board *board = createBoard();
    Card *deck = deckFromFile("../new.txt");
    loadDeck(board,deck);

    //TEST PRINT
    printBoard(board);

    //TEARDOWN
    clearBoard(board);
    printf("\n");
    printBoard(board);
    free(board);
}

void testPrintGameConsole(){
    char *lastCommand = "LD";
    char *message = "OK";
    printGameConsole(lastCommand,message);
}
int testBoard(){
    int result = 0;
    result += testCreateBoard();
    result += testLoadDeck() * 10;
    result += testClearBoard() * 100;
    return result;
}
