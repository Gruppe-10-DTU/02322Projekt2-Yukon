//
// Created by asbpo on 14-04-2023.
//
#include "filehandler.h"

Card *deckFromFile(char *filename){
    Card *deck = NULL;
    FILE *file = NULL;
    char* path = malloc(strlen(filename + 6));
    sprintf(path,"..\\%s", filename);
    char str[4];
    file = fopen (path, "r");
    if(file == NULL){
        printf("error");
        return NULL;
    }

    while (fgets(str, 4, file) != NULL){
        addCard(&deck, str[1], str[0]);
    }

    // Closing the file
    fclose(file);
    free(path);
    return deck;
}

void saveDeck(Card **deck, char *filename){
    FILE *file = NULL;
    char* path = malloc(strlen(filename + 6));
    sprintf(path,"..\\%s", filename);
    file = fopen(path, "a+");
    char check;
    if(fscanf(file, "c" ,check) == 0){
        return;
    }
    saveCard(*deck, file);
    free(path);
    fclose(file);
}

void saveCard(Card *card, FILE *file){
    if(card->nextCard != NULL){
        saveCard(card->nextCard, file);
        fputs("\r", file);
    }
    fputc(card->order, file);
    fputc(card->suit, file);

    /*

     */
}

Card *newDeck(){
    return deckFromFile("new.txt");
}