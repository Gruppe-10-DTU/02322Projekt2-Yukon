//
// Created by asbpo on 14-04-2023.
//
#include "filehandler.h"

Card *deckFromFile(char *filename){
    Card *deck = NULL;
    FILE *file = NULL;
    char *path = malloc(strlen(filename) + 6);

    sprintf(path,"..\\%s", filename);

    char str[4];
    int counter = 0;
    file = fopen (path, "r");
    if(file == NULL){
        printf("error");
        return NULL;
    }
    while (fgets(str, 4, file) != NULL){
        if(deckHasCard(deck, str[1], str[0]) == 1 || counter >= 52){
            freeDeck(deck);
            deck = NULL;
            printf("The deck file was not a valid deck.");
            break;
        }else{
            addCard(&deck, str[1], str[0]);
            counter++;
        }
    }

    // Closing the file
    fclose(file);
    return deck;
}



void saveDeck(Card *deck, char *filename){
    FILE *file = NULL;
    char* path = malloc(strlen(filename + 6));
    sprintf(path,"..\\%s", filename);
    file = fopen(path, "a+");
    char check;
    if(fscanf(file, "c" ,check) != 1){
        saveCard(deck, file);
    }
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
}

Card *newDeck(){
    return deckFromFile("new.txt");
}

int deckHasCard(Card *card, char suit, char order){
    if(card == NULL){
        return 1;
    }
    if(card->order == order && card->suit == suit){
        return 0;
    }else{
        return deckHasCard(card->nextCard, suit, order);
    }
};
