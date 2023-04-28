//
// Created by asbpo on 14-04-2023.
//
#include "filehandler.h"

Card *deckFromFile(char *filename){
    Card *deck;
    FILE *file = NULL;
    char *path = malloc(strlen(filename) + 6);

    sprintf(path,"..%s", filename);

    char str[4];
    file = fopen (path, "r");
    if(file == NULL){
        printf("error");
        return NULL;
    }

    while (fgets(str, 2, file) != NULL){
        printf(&str[0]);
        printf(&str[1]);

        addCard(&deck, str[1], str[0]);
    }

    // Closing the file
    fclose(file);
    return deck;
}

Card *newDeck(){
    return deckFromFile("nextDeck.txt");
}