//
// Created by asbpo on 14-04-2023.
//

#include "column.h"

void appendCard(Column **pColumn, Card **pCard) {
    if ((*pColumn)->tail == NULL) {
        (*pColumn)->tail = (*pCard);
        (*pColumn)->head = (*pCard);
    } else {
        Card *lastCard = (*pColumn)->tail;
        lastCard->nextCard = (*pCard);
        (*pCard)->prevCard = lastCard;
        (*pColumn)->tail = (*pCard);
    }
}
void moveCard(Column **From, Column **To, char faceVal){
    Card *current = NULL;
}


