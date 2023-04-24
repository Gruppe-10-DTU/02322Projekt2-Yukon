#include<stdlib.h>
#include<stdio.h>
#include "../column.h"
#include "column-test.h"

/**
 * @author Philip Astrup Cramer
 */
void testAppendToColumn(){
    //SETUP START
    Card *testcard1 = (Card *) malloc(sizeof(Card));
    testcard1->suit = 'H';
    testcard1->order = 'K';
    testcard1->visible = 1;
    testcard1->prevCard = NULL;
    testcard1->nextCard = NULL;

    Column *column1 = (Column *) malloc(sizeof(Column));
    column1->head = NULL;
    column1->tail = NULL;
    column1->size = 0;
    //SETUP FINISHED

    //TEST
    appendToColumn(&column1, &testcard1);
    if (column1->head == NULL) printf("\tDidn't update head\n");
    if (column1->tail == NULL) printf("\tDidn't update Tail\n");
    if (column1->size == 0) printf("\tDidn't update size\n");
    else printf("\tSuccess!\n");

    //TEARDOWN
    free(testcard1);
    free(column1);
}

/**
 * @author Philip Astrup Cramer
 */
void testMoveCard(){
    //SETUP START
    Card *queenSpades = (Card *) malloc(sizeof(Card));
    queenSpades->suit = 'S';
    queenSpades->order = 'Q';
    queenSpades->visible = 1;
    queenSpades->prevCard = NULL;
    queenSpades->nextCard = NULL;

    Card *kingHearts = (Card *) malloc(sizeof(Card));
    kingHearts->suit = 'H';
    kingHearts->order = 'K';
    kingHearts->visible = 1;
    kingHearts->prevCard = NULL;
    kingHearts->nextCard = NULL;

    Card *aceClubs = (Card *) malloc(sizeof(Card));
    aceClubs->suit = 'C';
    aceClubs->order = 'A';
    aceClubs->visible = 1;
    aceClubs->prevCard = NULL;
    aceClubs->nextCard = NULL;

    Card *jackHearts = (Card *) malloc(sizeof(Card));
    jackHearts->suit = 'H';
    jackHearts->order = 'J';
    jackHearts->visible = 1;
    jackHearts->prevCard = NULL;
    jackHearts->nextCard = NULL;

    Card *twoClubs = (Card *) malloc(sizeof(Card));
    twoClubs->suit = 'C';
    twoClubs->order = '2';
    twoClubs->visible = 1;
    twoClubs->prevCard = NULL;
    twoClubs->nextCard = NULL;

    Column *column1 = (Column *) malloc(sizeof(Column));
    column1->size = 0;
    column1->head = NULL;
    column1->tail = NULL;

    Column *column2 = (Column *) malloc(sizeof(Column));
    column2->size = 0;
    column2->head = NULL;
    column2->tail = NULL;

    Column *column3 = (Column *) malloc(sizeof(Column));
    column3->size = 0;
    column3->head = NULL;
    column3->tail = NULL;

    Column *foundation = (Column *) malloc(sizeof(Column));
    foundation->size = 0;
    foundation->head = NULL;
    foundation->tail = NULL;

    appendToColumn(&column1, &queenSpades);
    appendToColumn(&column1, &kingHearts);
    appendToColumn(&column2, &aceClubs);
    appendToColumn(&column2, &jackHearts);
    appendToColumn(&column3,&twoClubs);
    //SETUP FINISHED


    //TEST 1
    int c1SizeBeforeMove = column1->size;
    Card *c1HeadBeforeMove = column1->head;
    int c2SizeBeforeMove = column2->size;
    Card *c2HeadBeforeMove = column2->head;
    moveCard(&column2,&column1,jackHearts);
    if (c1SizeBeforeMove == column1->size || c1HeadBeforeMove == column1->head) printf("\tMove-1: Updating 'to' column failed\n");
    if (c2HeadBeforeMove == column2->head || c2SizeBeforeMove == column2->size) printf("\tMove-1: Updating 'from' column failed\n");
    else printf("\tMove-1: Success\n");

    //TEST 2
    c1HeadBeforeMove = column1->head;
    c1SizeBeforeMove = column1->size;
    int fSizeBeforeMove = foundation->size;
    Card *fHeadBeforeMove = foundation->head;
    moveCard(&column1, &foundation, aceClubs);
    if (fSizeBeforeMove == foundation->size || fHeadBeforeMove == foundation->head) printf("\tMove-2: Updating 'to' column failed\n");
    if (c1SizeBeforeMove == column1->size || c1HeadBeforeMove == column1->head) printf("\tMove-2: Updating 'from' column failed\n");
    else printf("\tMove-2: Success\n");

    //TEARDOWN
    free(queenSpades);
    free(kingHearts);
    free(aceClubs);
    free(jackHearts);
    free(twoClubs);
    free(column1);
    free(column2);
    free(column3);
    free(foundation);
}

/**
 * @author Philip Astrup Cramer
 */
void testMoveIsValid(){
    //SETUP START
    Card *queenSpades = (Card *) malloc(sizeof(Card));
    queenSpades->suit = 'S';
    queenSpades->order = 'Q';
    queenSpades->visible = 1;
    queenSpades->prevCard = NULL;
    queenSpades->nextCard = NULL;

    Card *kingHearts = (Card *) malloc(sizeof(Card));
    kingHearts->suit = 'H';
    kingHearts->order = 'K';
    kingHearts->visible = 1;
    kingHearts->prevCard = NULL;
    kingHearts->nextCard = NULL;

    Card *aceClubs = (Card *) malloc(sizeof(Card));
    aceClubs->suit = 'C';
    aceClubs->order = 'A';
    aceClubs->visible = 1;
    aceClubs->prevCard = NULL;
    aceClubs->nextCard = NULL;

    Card *jackHearts = (Card *) malloc(sizeof(Card));
    jackHearts->suit = 'H';
    jackHearts->order = 'J';
    jackHearts->visible = 1;
    jackHearts->prevCard = NULL;
    jackHearts->nextCard = NULL;

    Card *twoClubs = (Card *) malloc(sizeof(Card));
    twoClubs->suit = 'C';
    twoClubs->order = '2';
    twoClubs->visible = 1;
    twoClubs->prevCard = NULL;
    twoClubs->nextCard = NULL;

    Column *column1 = (Column *) malloc(sizeof(Column));
    column1->size = 0;
    column1->head = NULL;
    column1->tail = NULL;

    Column *column2 = (Column *) malloc(sizeof(Column));
    column2->size = 0;
    column2->head = NULL;
    column2->tail = NULL;

    Column *column3 = (Column *) malloc(sizeof(Column));
    column3->size = 0;
    column3->head = NULL;
    column3->tail = NULL;

    Column *foundation = (Column *) malloc(sizeof(Column));
    foundation->size = 0;
    foundation->head = NULL;
    foundation->tail = NULL;

    appendToColumn(&column1, &queenSpades);
    appendToColumn(&column1, &kingHearts);
    appendToColumn(&column2, &aceClubs);
    appendToColumn(&column2, &jackHearts);
    //SETUP FINISH

    //TEST
    if (!(moveIsValid(&jackHearts, &column1, 0))) printf("\tFailed column check 1\n");
    if (!(moveIsValid(&aceClubs, &foundation, 1))) printf("\tFailed foundation check\n");
    if (!(moveIsValid(&jackHearts, &column1, 0))) printf("\tFailed column check 2\n");
    if (!(moveIsValid(&kingHearts, &column3, 0))) printf("\tFailed move to empty column check\n");
    else printf("\tSuccess!\n");

    //TEARDOWN
    free(queenSpades);
    free(kingHearts);
    free(aceClubs);
    free(jackHearts);
    free(twoClubs);
    free(column1);
    free(column2);
    free(column3);
    free(foundation);
}

/**
 * @author Philip Astrup Cramer
 */
void columnTest(){
    printf("Append card test result:\n");
    testAppendCard();
    printf("Move card test result:\n");
    testMoveCard();
    printf("Move is valid test result:\n");
    testMoveIsValid();

}