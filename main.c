//
// Created by asbpo on 14-04-2023.
//
#include "filehandler.h"
#include "deck.h"
#include "board.h"

int main(){
    //Terminal input/output
    clearView();
    printTitle();

    //Reader

    //Nyt deck
    Card *deck = deckFromFile("invalidDeckTooManyCards.txt");
    deck = deckFromFile("invalidDeckDublicateCards.txt");

    return 0;
}