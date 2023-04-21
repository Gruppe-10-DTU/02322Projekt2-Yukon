//
// Created by asbpo on 14-04-2023.
//
#include "filehandler.h"
#include "deck.h"

int main(){
    //Terminal input/output

    //Reader

    //Nyt deck
    Card *deck = deckFromFile("invalidDeckTooManyCards.txt");
    deck = deckFromFile("invalidDeckDublicateCards.txt");

    return 0;
}