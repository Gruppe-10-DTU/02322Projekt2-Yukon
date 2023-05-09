//
// Created by pcramer on 14-04-2023.
//

#include "column.h"

/**
 *
 * @param pColumn target column
 * @param pCard card to add
 *
 * @author Philip Astrup Cramer
 */
void addToColumn(Column *pColumn, Card *pCard){
    if ((pColumn)->tail == NULL && (pColumn)->head == NULL) {
        (pColumn)->tail = (pCard);
        (pColumn)->head = (pCard);
        pCard->prevCard = NULL;
        pCard->nextCard = NULL;
    } else {
        Card *prevHead = (pColumn)->head;
        prevHead->prevCard = (pCard);
        (pCard)->nextCard = prevHead;
        (pColumn)->head = (pCard);
        (pCard)->prevCard = NULL;
    }
    (pColumn)->size += 1;
}


/**
 *
 * @param pColumn target column
 * @param pCard card to append
 *
 * @author Philip Astrup Cramer
 */
void appendToColumn(Column *pColumn, Card *pCard) {
    if ((pColumn)->tail == NULL && (pColumn)->head == NULL) {
        (pColumn)->tail = (pCard);
        (pColumn)->head = (pCard);
        pCard->prevCard = NULL;
        pCard->nextCard = NULL;
    } else {
        Card *lastCard = (pColumn)->tail;
        lastCard->nextCard = (pCard);
        (pCard)->prevCard = lastCard;
        (pColumn)->tail = (pCard);
    }
    (pColumn)->size += 1;
}

/**
 *
 * @param from origin column
 * @param to destination column
 * @param mvCard the card to be moved
 *
 * @author Philip Astrup Cramer
 */
void moveCard(Column *from, Column *to, Card *mvCard) {
    Card *current = NULL;
    int mvCount = 1;
    //Iterates through the 'from' column until match or end is found
    for (current = from->head; current != mvCard; current = current->nextCard) {
        mvCount++;
        if (current == NULL) return;
    }
    //updates the head of the 'from' column
    from->head = current->nextCard;
    if (!from->head) {
        from->tail = NULL;
    } else {
        from->head->prevCard = NULL;
    }
    if (from->head != NULL && from->head->visible != 1) {
        from->head->visible = 1;
    }
    from->size -= mvCount;
    //Moves the card and finds new head of the column

    current->nextCard = to->head;
    if(to->head) to->head->prevCard = current;
    if(!to->tail) to->tail = current;
    for(current = current; current->prevCard; current = current->prevCard){
    }
    to->head = current;
    to->size += mvCount;
}

/**
 * @param mvCard pointer to the card to move
 * @param to the place to move
 * @param toFoundation int 1 represents a move to foundation
 * @return 1 if valid
 *
 * @author Philip Astrup Cramer
 */
int moveIsValid(Card *mvCard, Column *to, int toFoundation){
    if(!((mvCard)->visible)) return 0;
    for(Card *temp = to->head; temp; temp = temp->nextCard)
        if(temp == mvCard) return 0;
    char mvSuit = (mvCard)->suit;
    char mvOrder = (mvCard)->order;
    if (to->head == NULL && ((!mvCard->prevCard && toFoundation && mvOrder == 'A') || (!toFoundation && mvOrder == 'K'))) return 1;
    else if ((to)->head == NULL) return 0;
    char toSuit = (to)->head->suit;
    char toOrder = (to)->head->order;
    int direction = 1;
    if(toFoundation) direction *= -1;
    char deck0rder[14] = {'\0', 'A', '2','3','4','5','6','7','8','9','T','J','Q','K'};
    if((mvSuit != toSuit) ^ (toFoundation)){                        // if to foundation suit's cant match
        int mvOrderval, toOrderVal;
        for (int i = 1; i < 14; i++){                               //
            if(mvOrder == deck0rder[i]) mvOrderval = i;             // Translates the char value of the card to an integer
            if(toOrder == deck0rder[i]) toOrderVal = i;             //
        }
        if(toOrderVal - mvOrderval == 1 * direction) return 1;      // Difference between cards must be 1
    }
    return 0;
}




