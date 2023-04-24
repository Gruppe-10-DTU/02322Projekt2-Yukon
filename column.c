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
    (*pColumn)->size += 1;
}
void moveCard(Column **from, Column **to, Card *mvCard){
    Card *current = (*from)->head;
    int mvCount = 1;
    //Iterates through the 'from' column until match or end is found
    while(current->suit != mvCard->suit && current->order != mvCard->order){
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
    if((*to)->tail == NULL) (*to)->tail = current;
    while(current->prevCard != NULL){
        current = current->prevCard;
    }
    (*to)->head = current;
    (*to)->size += mvCount;
}
int moveIsValid(Card **mvCard, Column **to, int toFoundation){
    if(!((*mvCard)->visible)) return 0;
    char mvSuit = (*mvCard)->suit;
    char mvOrder = (*mvCard)->order;
    if ((*to)->head == NULL && ((toFoundation && mvOrder == 'A') || (!toFoundation && mvOrder == 'K'))) return 1;
    else if ((*to)->head == NULL) return 0;
    char toSuit = (*to)->head->suit;
    char toOrder = (*to)->head->order;
    int direction = 1;
    if(toFoundation) direction *= -1;
    if((mvSuit != toSuit) ^ (toFoundation)){                        // if to foundation suit's cant match
        if(toOrder - mvOrder ==  1 * direction) return 1;           // normal number difference
        else if (toOrder - mvOrder == -6 * direction) return 1;     // K - Q
        else if (toOrder - mvOrder == 7 * direction) return 1;      // Q - J
        else if (toOrder - mvOrder == -10 * direction) return 1;    // Q - J
        else if (toOrder - mvOrder == 27 * direction) return 1;     // T - 9
        else if (toOrder - mvOrder == -15 * direction) return 1;    // 2 - A
        else return 0;
    }
    return 0;
}


