//
// Created by asbpo on 14-04-2023.
//
#include "deck.h"

void addCard(Card **head,char suit, char order){
    Card *newCard;
    newCard = (Card *) malloc(sizeof(Card));
    newCard->order = order;
    newCard->suit = suit;
    newCard->visible = 0;
    if (*head == NULL){
        *head = newCard;
        newCard->nextCard = NULL;
    } else{
        newCard->nextCard = *head;
        *head = newCard;
    }
};










