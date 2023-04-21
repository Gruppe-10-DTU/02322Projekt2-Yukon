//
// Created by asbpo on 14-04-2023.
//
#include <stdio.h>
#include "board.h"
#include "deck.h"
#include "column.h"
#include "stdio.h"
int const columns = 7;
Column* c;
Card* findCardX(Column* cou, int X){
    if(X > cou->size){
        return NULL;
    }else {
        Card *tmp1;
        tmp1 = c->head;
        for (int i = 0; i < X; i++) {
            if(tmp1->visible != 1){
                return NULL;
            }
            tmp1 = tmp1->nextCard;
        }
        return tmp1;
    }
}

int findLargestColumn(Column* cou){
    int MAXSIZE = 0;
    for (int i = 0; i < columns; ++i) {
        if(cou[i].size > MAXSIZE){
            MAXSIZE = cou->size;
        }
    }
    return MAXSIZE;
}

void printBoard(Column * cou){
    for(int i = 0; i < findLargestColumn(c)+1; i++){
        for (int j = 0; j < columns; ++j) {
            char* tmp = (char*) malloc(100 * sizeof(char));
            if(findCardX(&cou[j],j)->visible != 0) {
                sprintf(tmp, "%c%c", findCardX(&cou[j], j)->suit, findCardX(&cou[j], j)->order);
                printf("   %s", tmp != NULL ? tmp : " ");
                free(tmp);
            }else{
                printf("   %s","[]");
                free(tmp);
            }
        }
        printf("%s\n","");
    }
};






