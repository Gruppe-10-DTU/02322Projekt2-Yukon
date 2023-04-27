//
// Created by asbpo on 14-04-2023.
//
#include "board.h"
#include "deck.h"
#include "column.h"

void printBoard(Column columns[7],Column foundations[4]){
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    Card *indexLine[7];
    for(int i = 0; i < 7; i++) {
        indexLine[i] = columns[i].tail;
    }
    int allDone = 0;
    int lineCount = 0;
    while(!allDone){
        int rowCount = 0;
        while (rowCount < 7){
            if(indexLine[rowCount] == NULL){
                printf("\t");
            } else if (!indexLine[rowCount]->visible){
                printf("[]\t");
                indexLine[rowCount] = indexLine[rowCount]->prevCard;
            } else {
                printf("%c%c\t", indexLine[rowCount]->order, indexLine[rowCount]->suit);
                indexLine[rowCount] = indexLine[rowCount]->prevCard;
            }
            rowCount++;
        }
        if(lineCount < 7 && lineCount % 2 == 0){
            printf("\t");
            if(foundations[lineCount / 2].head != NULL){
                printf("%c%c", foundations[rowCount / 2].head->order, foundations[rowCount / 2].head->suit);
            } else{
                printf("[]");
            }
            printf("\tF%d", (lineCount / 2) + 1);
        }
        allDone = 1;
        for(int j = 0; j < 7; j++){
            if (indexLine[j] != NULL) allDone = 0;
        }
        printf("\n");
        lineCount++;
    }
    fflush(stdin);
}
void printGameConsole(char *lastCommand, char *message){
    printf("LAST Command: %s\n", lastCommand);
    printf("MESSAGE: %s\n",message);
    printf("INPUT >");
}

void clearView(){

}





