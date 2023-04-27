//
// Created by pcramer on 4/26/23.
//

#include "board-test.h"


void testPrintboard() {
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
    Card *topCard = deck;
    while(i < 7 && topCard != NULL && columnCount[i]){
        deck = deck->nextCard;
        addToColumn(&columns[i],topCard);
        topCard = deck;
        columnCount[i]--;
        if(columnCount[i] == 0) {
            i++;
        }
    }
    //SETUP DONE

    //TEST PRINT
    printBoard(columns,foundations);

    //TEARDOWN
    free(topCard);
    for(int j = 0; j < 7; j++){
        while(columns[j].head != NULL){
            Card *tmp = columns[j].head->nextCard;
            free(columns[j].head);
            columns[j].head = tmp;
        }
    }
}
void testPrintGameConsole(){
    char *lastCommand = "LD";
    char *message = "OK";
    printGameConsole(lastCommand,message);
}
