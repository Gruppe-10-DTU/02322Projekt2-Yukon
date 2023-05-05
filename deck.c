//
// Created by asbpo on 14-04-2023.
//
#include "deck.h"
#include<stdlib.h>


void addCard(Card **head,char suit, char order){
    Card *newCard;
    newCard = (Card *) malloc(sizeof(Card));
    newCard->order = order;
    newCard->suit = suit;
    newCard->visible = 0;
    newCard->prevCard = NULL;
    if (*head == NULL){
        *head = newCard;
        newCard->nextCard = NULL;
    } else{
        newCard->nextCard = *head;
        (*head)->prevCard = newCard;
        *head = newCard;
    }
};

int countDeck(Card *head){
    int counter = 1;
    Card *item = head;
    while(item->nextCard != NULL){
        counter++;
        item = item->nextCard;
    }
    return counter;
}

void shuffle(Card **head){
    int placementMax, placementCurrent;
    Card *whileLoopCard, *tmp, *shuffledDeck, *placeholder, *nextCard;
    if(head == NULL){
        return;
    }
    //Int that says how many places a card can be
    placementMax = 1;

    //Set shuffledDeck to the first card in head
    shuffledDeck = *head;
    whileLoopCard = shuffledDeck->nextCard;
    shuffledDeck->nextCard = NULL;

    while(whileLoopCard != NULL){
        nextCard = whileLoopCard->nextCard;
        //whileLoopCard->nextCard = NULL;
        //whileLoopCard->prevCard = NULL;
        //Find the place for the card based on how many cards are placed.
        //The shuffle always start with one card
        placementCurrent =  (rand() % (placementMax+1));

        //If placementCurrent is 0, add it to the start
        if(placementCurrent == 0){
            whileLoopCard->nextCard = shuffledDeck;
            shuffledDeck->prevCard = whileLoopCard;
            whileLoopCard->prevCard = NULL;
            shuffledDeck = whileLoopCard;
        }else{
            placeholder = shuffledDeck;

            //Get the pointer where nextCard is the placement
            for (int i = 1; i< placementCurrent; i++){
                placeholder = placeholder->nextCard;
            }
            if(placeholder->nextCard == NULL){
                placeholder->nextCard = whileLoopCard;
                whileLoopCard->prevCard = placeholder;
                whileLoopCard->nextCard = NULL;
            }else{
                //Break the linked list and put in the card.
                tmp = placeholder->nextCard;
                tmp->prevCard = whileLoopCard;
                placeholder->nextCard = whileLoopCard;
                whileLoopCard->nextCard = tmp;
                whileLoopCard->prevCard = placeholder;
            }
        }
        whileLoopCard = nextCard;
        placementMax++;
    }

    *head = shuffledDeck;
}

void freeDeck(Card *head){
    Card *tmp;
    while (head != NULL){
        tmp = head->nextCard;
        free(head);
        head = tmp;
    }
}

/**
 * Splits the deck based on a split index.
 * @param head The deck you want split
 * @param splitIndex The size of the first bunk. Set -1 if you want it done randomly.
 * If set to 0 or 52, it will just return the deck unchanged.
 */
void split(Card **head, int splitIndex){
    Card *firstDeck = *head, *secondDeck = firstDeck, *shufflePile;
    if(splitIndex == -1){
        splitIndex = (rand() % (52));
    }else if(splitIndex == 0 || splitIndex >= 52 || head == NULL){
        return;
    }
    for (int i = 0; i < splitIndex; ++i) {
        secondDeck = secondDeck->nextCard;
        firstDeck = firstDeck->nextCard;
    }
    firstDeck = firstDeck->prevCard;
    firstDeck->nextCard = NULL;
    for (int i = 1; i < splitIndex; ++i) {
        firstDeck = firstDeck->prevCard;
    }

    //Clean up the previous card on the two decks.
    firstDeck->prevCard = NULL;
    secondDeck->prevCard = NULL;

    //Set the shuffle pile to the first card of the first deck
    shufflePile = firstDeck;
    firstDeck = firstDeck->nextCard;

    while(firstDeck != NULL && secondDeck != NULL){
        shufflePile->nextCard = secondDeck;
        secondDeck->prevCard = shufflePile;
        shufflePile = shufflePile->nextCard;
        secondDeck = secondDeck->nextCard;

        shufflePile->nextCard = firstDeck;
        firstDeck->prevCard = shufflePile;
        shufflePile = shufflePile->nextCard;
        firstDeck = firstDeck->nextCard;
    }
    if(firstDeck == NULL){
        while(secondDeck != NULL){
            shufflePile->nextCard = secondDeck;
            secondDeck->prevCard = shufflePile;
            shufflePile = shufflePile->nextCard;
            secondDeck = secondDeck->nextCard;
        }
    }else{
        while(firstDeck != NULL){
            shufflePile->nextCard = firstDeck;
            firstDeck->prevCard = shufflePile;
            shufflePile = shufflePile->nextCard;
            firstDeck = firstDeck->nextCard;
        }
    }
    *head = shufflePile;
}









Card* findCard(Card* cards, char suit, char order){
    while(cards != NULL){
        if(cards->order == order && cards->suit == suit){
            return cards;
        }
        cards = cards->nextCard;
    }
    return NULL;
}









