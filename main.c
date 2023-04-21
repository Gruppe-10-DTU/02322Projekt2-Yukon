//
// Created by asbpo on 14-04-2023.
//
#include "filehandler.h"
#include "deck.h"
#include "board.h"
char *cmd;
char *lstcmd;
int validation;
char *valid ="\0";

char * translateValidation(int validation){
    if(validation == 1 || validation != NULL ? validation : 1){
        valid = "OK";
    }else{
        valid = "ERROR";
    }
};

void printConsoleWindow(){
    printf("\n LAST COMMAND: %s",lstcmd != NULL ? lstcmd : "");
    printf("\n STATUS: %s", translateValidation(validation));
    printf("\n INPUT > %s", cmd != NULL ? cmd : "");

}

void getCommand(){
    free(cmd);
    char *temp;
    if(validation != 0){
        if(cmd != NULL){
            free(lstcmd);
            lstcmd = malloc(strlen(cmd+1) + sizeof(char));
            strcpy(lstcmd,cmd);
            lstcmd[strlen(cmd)] = '\0';
        }
    }else{
        lstcmd = lstcmd;
    }
    printConsoleWindow();
    scanf("%ms",&temp);
    cmd = temp;
    free(temp);
}

void clearConsole(){
    printf("%s\n\n\n\n\n\n\n\n\n","");
}

int main(){
    //Terminal input/output
    printConsoleWindow();
    clearConsole();
    //Reader

    //Nyt deck
    Card *deck = newDeck();
    //j


    return 0;
}