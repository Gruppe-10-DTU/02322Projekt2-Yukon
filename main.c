//
// Created by asbpo on 14-04-2023.
//
#include "filehandler.h"
#include "deck.h"
#include "board.h"
#include "board.h"
#include "column.h"

int main(){
    //Terminal input/output
    clearView();
    printTitle();

    //Reader
    //SETUP START
    Card *deck = deckFromFile("../new.txt");
    Column columns[7];
    for (int i = 0; i < 7; i++) {
        columns[i].head = NULL;
        columns[i].tail = NULL;
        columns[i].size = 0;
    }
    Column foundations[4];
    for (int i = 0; i < 4; i++) {
        foundations[i].head = NULL;
        foundations[i].tail = NULL;
        foundations[i].size = 0;
    }
    int columnCount[7] = {1,6,7,8,9,10,11};
    int i = 0;
    while(deck != NULL){
        if(columnCount[i] < &columns[i].size){
            addToColumn(&columns[i],deck);
            deck = deck->nextCard;
        }
        i++;
    }
    //TEST PRINT
    printBoard(columns,foundations);

    //Nyt deck
    Card *deck = newDeck();
    //j

    return 0;
}