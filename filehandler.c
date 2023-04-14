//
// Created by asbpo on 14-04-2023.
//
#include "filehandler.h"


Card *deckFromFile(char *filename){
    FILE *file = NULL;
    char str[3];
    file = fopen ("new.txt", "r");
    if(file == NULL){
        printf("error");
        return NULL;
    }

    while (fgets(str, 2, file) != NULL){
        printf("%s", str);
    }

    // Closing the file
    fclose(file);
}

Card *newDeck(){
    return deckFromFile("nextDeck.txt");
}