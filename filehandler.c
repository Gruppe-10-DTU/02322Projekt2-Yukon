//
// Created by asbpo on 14-04-2023.
//
#include "filehandler.h"

Card *deckFromFile(char *filename, char *statusMsg){
    Card *deck = NULL;
    FILE *file = NULL;
    char *path = malloc(strlen(filename) + 6);
    #ifdef __WIN32__
        char *pathFormat = "..\\%s";
    #elifdef __linux__
        char *pathFormat = "../%s";
    #endif

    sprintf(path,pathFormat, filename);

    char str[4];
    file = fopen (path, "r");
    if(file == NULL){
        strcpy(statusMsg,"File does not exist");
        return NULL;
    }
    int i;
    while (fgets(str, 4, file) != NULL){
        i = 0;
        if(!deckIsValid(deck, str[1], str[0], i, statusMsg)){
            freeDeck(deck);
            deck = NULL;
            break;
        }else{
            addCard(&deck, str[1], str[0]);
        }
    }

    // Closing the file
    fclose(file);
    return deck;
}



void saveDeck(Card *deck, char *filename){
    FILE *file = NULL;
    char* path = malloc(strlen(filename + 6));
    sprintf(path,"../%s", filename);
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

Card *newDeck(char *statusMsg){
    return deckFromFile("new.txt", statusMsg);
}

int deckIsValid(Card *card, char suit, char order, int counter, char *statusMsg){
    if(card == NULL){
        strcpy(statusMsg, "OK");
        return 1;
    }else if(card->order == order && card->suit == suit) {
        strcpy(statusMsg,"The deck has duplicate cards");
        return 0;
    }else if(counter >= 52){
        strcpy(statusMsg, "The deck contains too many cards");
        return 0;
    }else{
        return deckIsValid(card->nextCard, suit, order, counter++, statusMsg);
    }
};
