//
// Created by asbpo on 14-04-2023.
//
#include "filehandler.h"

Card *deckFromFile(char *filename, char *statusMsg){
    Card *deck = NULL;
    FILE *file = NULL;
    char *path = malloc(strlen(filename) + 6);
    #ifdef __WIN32__
        sprintf(path,"..\\%s", filename);
    #elif __linux__
        sprintf(path,"../%s", filename);
    #endif

    //sprintf(path,"..\\%s", filename);

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
            fclose(file);
            free(path);
            return deck;
        }else{
            addCard(&deck, str[1], str[0]);
        }
    }

    // Closing the file
    fclose(file);
    free(path);
    if(countDeck(deck) != 52){
        strcpy(statusMsg,"Deck doesn't have 52 cards");
        freeDeck(deck);
        return NULL;
    }
    return deck;
}



void saveDeck(Card *deck, char *filename){
    FILE *file = NULL;
    char* path = malloc(strlen(filename + 6));
    #ifdef __WIN32__
        sprintf(path,"..\\%s.txt", filename);
    #elif __linux__
        sprintf(path,"../%s.txt", filename);
    #endif
    file = fopen(path, "a+");
    char check;
    if(fscanf(file, "c" ,check) != 1){
        saveCard(deck, file);
    }else{
        printf("Error saving deck, file already existed");
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
        strcpy(statusMsg,statusMsg);
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
