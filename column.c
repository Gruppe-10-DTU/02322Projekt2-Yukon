//
// Created by asbpo on 14-04-2023.
//

#include "column.h"

void appendCard(Column **pColumn, Card **pCard) {
    if ((*pColumn)->tail == NULL && (*pColumn)->head == NULL) {
        (*pColumn)->tail = (*pCard);
        (*pColumn)->head = (*pCard);
    } else {
        Card *lastCard = (*pColumn)->tail;
        lastCard->nextCard = (*pCard);
        (*pCard)->prevCard = lastCard;
        (*pColumn)->tail = (*pCard);
    }
}
void moveCard(Column **from, Column **to, char faceVal[]){
    Card *current = (*from)->head;
    int mvCount = 1;
    //Iterates throug the from coloumn until match or end is found
    while(current->suit != faceVal[1] && current->order != faceVal[0]){
        current = current->nextCard;
        mvCount++;
        if(current == NULL) return;
    }
    //updates the head of the from column
    (*from)->head = current->nextCard;
    if((*from)->head == NULL){
        (*from)->tail = NULL;
    }else {
        (*from)->head->prevCard = NULL;
    }
    (*from)->size -= mvCount;

    //Moves the card and finds new head of the column
    current->nextCard = (*to)->head;
    while(current->prevCard != NULL){
        current = current->prevCard;
    }
    (*to)->head = current;
    (*to)->size += mvCount;
}



