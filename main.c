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
    Card *deck = deckFromFile("new.txt");
    shuffle(&deck);
    int counter = 0;
    Card *tmp;
    while (deck != NULL && counter < 60){
        tmp = deck->nextCard;
        //printf("%c%c \r\n", tmp->order, tmp->suit);
        deck = tmp;
        counter++;
    }
    printf("%d", counter);
    return 0;
}