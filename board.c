//
// Created by asbpo on 14-04-2023.
//
#include "board.h"
#include "deck.h"
#include "column.h"

Board *createBoard(){
    Board *board = (Board *) malloc(sizeof(Board));

    Column columns[7];
    for (int i = 0; i < 7; i++) {
        columns[i].head = NULL;
        columns[i].tail = NULL;
        columns[i].size = 0;
        board->column[i] = columns[i];
    }
    Column foundations[4];
    for (int i = 0; i < 4; i++) {
        foundations[i].head = NULL;
        foundations[i].tail = NULL;
        foundations[i].size = 0;
        board->foundation[i] = foundations[i];
    }
    return board;
}

void loadDeck(Board *board, Card *deck){
    int columnCount[7] = {1,6,7,8,9,10,11};
    int i = 0;

    Card *topCard = deck;
    while(i < 7 && topCard != NULL && columnCount[i]){
        deck = deck->nextCard;
        addToColumn(&board->column[i],topCard);
        topCard = deck;
        columnCount[i]--;
        if(columnCount[i] == 0) {
            i++;
        }
    }
}
void clearBoard(Board *board){
    for(int j = 0; j < 7; j++){
        while(board->column[j].head != NULL){
            Card *tmp = board->column[j].head->nextCard;
            free(board->column[j].head);
            board->column[j].head = tmp;
        }
        board->column[j].tail = NULL;
        board->column[j].size = 0;
    }
    for(int j = 0; j < 4; j++){
        while(board->foundation[j].head != NULL){
            Card *tmp = board->foundation[j].head->nextCard;
            free(board->foundation[j].head);
            board->foundation[j].head = tmp;
        }
        board->foundation[j].tail = NULL;
        board->foundation[j].size = 0;
    }

}

void printBoard(Board *board){
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    Column *columns = board->column;
    Column *foundations = board->foundation;
    Card *indexLine[7];
    for(int i = 0; i < 7; i++) {
        indexLine[i] = columns[i].tail;
    }
    int allDone = 0;
    int lineCount = 0;
    while(!allDone && lineCount < 7){
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
        if(lineCount % 2 == 0){
            printf("\t");
            if(foundations[lineCount / 2].head != NULL){
                printf("%c%c", foundations[rowCount / 2].head->order, foundations[rowCount / 2].head->suit);
            } else{
                printf("[]");
            }
            printf("\tF%d", (lineCount / 2) + 1);
        }
        printf("\n");
        lineCount++;
        if(lineCount== 7) allDone = 1;
        for(int j = 0; j < 7; j++){
            if (indexLine[j] != NULL) allDone = 0;
        }
    }
    fflush(stdin);
}
void printGameConsole(char *lastCommand, char *message){
    printf("LAST Command: %s\n", lastCommand);
    printf("MESSAGE: %s\n",message);
    printf("INPUT >");
}

void clearView(){
#ifdef __linux__
    system("clear");
#elif __WIN32__
    system("clear");
#endif
}





