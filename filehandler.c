//
// Created by asbpo on 14-04-2023.
//
#include "filehandler.h"

Card *deckFromFile(char *filename){
    Card *deck = NULL;
    FILE *file = NULL;
    char *path = filename;//"C:\\Users\\asbpo\\CLionProjects\\02322Projekt2-Yukon\\new.txt";
    char str[4];
    file = fopen (path, "r");
    if(file == NULL){
        printf("error");
        return NULL;
    }

    while (fgets(str, 4, file) != NULL){
        //printf("%c",str[0]);
        //printf("%c\n",str[1]);

        addCard(&deck, str[1], str[0]);
    }

    // Closing the file
    fclose(file);
    return deck;
}

Card *newDeck(){
    return deckFromFile("nextDeck.txt");
}