//
// Created by asbpo on 14-04-2023.
//
#include <stdio.h>
#include "board.h"
#include "deck.h"
#include "column.h"
#include "stdio.h"
int const columns = 7;


//Find card X from the head in column cou.
Card* findCardX(Column* cou, int X){
    if(X > cou->size){
        //If we exceed the column size, we should return NULL.
        return NULL;
    }else {
        Card *tmp1;
        tmp1 = cou->head;
        for (int i = 0; i < X; i++) {
            if(tmp1->visible != 1){
                //If the cards is not visible to the player, we should return NULL.
                return NULL;
            }
            tmp1 = tmp1->nextCard;
        }
        return tmp1;
    }
}

//Find the largest column of all the 7 specified columns.
int findLargestColumn(Column* cou){
    int MAXSIZE = 0;
    for (int i = 0; i < columns; ++i) {
        if(cou[i].size > MAXSIZE){
            MAXSIZE = cou->size;
        }
    }
    return MAXSIZE;
}
//Print the board in the console.
void printBoard(Column* cou){
    for(int i = 0; i < findLargestColumn(cou)+1; i++){
        //We want to print the cards row-wise. So we start in row 1, then row 2 and so forth. Each card has to be printed it is respective column.
        for (int j = 0; j < columns; ++j) {
            char* tmp = (char*) malloc(100 * sizeof(char));
            //If the card is visible we should print the information, if not, then we should print the [] as specified.
            if(findCardX(&cou[j],i)->visible != 0) {
                //Concatenate the information suit and order.
                sprintf(tmp, "%c%c", findCardX(&cou[j], i)->suit, findCardX(&cou[j], i)->order);
                //Print the information for the player.
                printf("   %s", tmp != NULL ? tmp : " ");
                free(tmp);
            }else{
                printf("   %s","[]");
                free(tmp);
            }
        }
        //Go to next row.
        printf("%s\n","");
    }
};






