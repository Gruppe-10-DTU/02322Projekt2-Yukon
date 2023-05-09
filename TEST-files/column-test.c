#include<stdlib.h>
#include "../column.h"
#include "column-test.h"

/**
 * @author Philip Astrup Cramer
 */
int testAddToColumn() {
    int result = 0;
    //SETUP START
    Card *testcard1 = (Card *) malloc(sizeof(Card));
    testcard1->suit = 'H';
    testcard1->order = 'K';
    testcard1->visible = 1;
    testcard1->prevCard = NULL;
    testcard1->nextCard = NULL;

    Card *testcard2 = (Card *) malloc(sizeof(Card));
    testcard2->suit = 'S';
    testcard2->order = 'Q';
    testcard2->visible = 1;
    testcard2->prevCard = NULL;
    testcard2->nextCard = NULL;

    Column *column1 = (Column *) malloc(sizeof(Column));
    column1->head = NULL;
    column1->tail = NULL;
    column1->size = 0;
    //SETUP FINISHED

    //TEST 1
    addToColumn(column1, testcard1);
    if (column1->head == NULL) result++;
    if (column1->tail == NULL) result++;
    if (column1->size == 0) result++;

    //TEST 2
    addToColumn(column1, testcard2);
    if (column1->head == testcard1) result++;
    if (testcard1->prevCard != testcard2 || testcard2->nextCard != testcard1) result++;
    if (column1->size == 1) result++;
    //TEARDOWN
    free(testcard1);
    free(testcard2);
    free(column1);

    return result;
}

/**
 * @author Philip Astrup Cramer
 */
int testAppendToColumn(){
    int result = 0;
    //SETUP START
    Card *testcard1 = (Card *) malloc(sizeof(Card));
    testcard1->suit = 'H';
    testcard1->order = 'K';
    testcard1->visible = 1;
    testcard1->prevCard = NULL;
    testcard1->nextCard = NULL;

    Card *testcard2 = (Card *) malloc(sizeof(Card));
    testcard2->suit = 'S';
    testcard2->order = 'Q';
    testcard2->visible = 1;
    testcard2->prevCard = NULL;
    testcard2->nextCard = NULL;

    Column *column1 = (Column *) malloc(sizeof(Column));
    column1->head = NULL;
    column1->tail = NULL;
    column1->size = 0;
    //SETUP FINISHED

    //TEST
    appendToColumn(column1, testcard1);
    if (column1->head == NULL) result++;
    if (column1->tail == NULL) result++;
    if (column1->size == 0) result++;

    //TEST 2
    appendToColumn(column1, testcard2);
    if (column1->tail == testcard1) result++;
    if (testcard1->nextCard != testcard2 || testcard2->prevCard != testcard1) result++;
    if (column1->size == 1) result++;

    //TEARDOWN
    free(testcard1);
    free(column1);

    return result;
}

/**
 * @author Philip Astrup Cramer
 */
int testMoveCard(){
    int result = 0;
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

    appendToColumn(column1, queenSpades);
    appendToColumn(column1, kingHearts);
    appendToColumn(column2, aceClubs);
    appendToColumn(column2, jackHearts);
    appendToColumn(column3,twoClubs);
    //SETUP FINISHED


    //TEST 1
    int c1SizeBeforeMove = column1->size;
    Card *c1HeadBeforeMove = column1->head;
    int c2SizeBeforeMove = column2->size;
    Card *c2HeadBeforeMove = column2->head;
    moveCard(column2,column1,jackHearts);
    if (c1SizeBeforeMove == column1->size || c1HeadBeforeMove == column1->head) result++;
    if (c2HeadBeforeMove == column2->head || c2SizeBeforeMove == column2->size) result++;


    //TEST 2
    c1HeadBeforeMove = column1->head;
    c1SizeBeforeMove = column1->size;
    int fSizeBeforeMove = foundation->size;
    Card *fHeadBeforeMove = foundation->head;
    moveCard(column1, foundation, aceClubs);
    if (fSizeBeforeMove == foundation->size || fHeadBeforeMove == foundation->head) result++;
    if (c1SizeBeforeMove == column1->size || c1HeadBeforeMove == column1->head) result++;

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

    return result;
}

/**
 * @author Philip Astrup Cramer
 */
int testMoveIsValid(){
    int result = 0;
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

    addToColumn(column1, kingHearts);
    addToColumn(column1, queenSpades);

    addToColumn(column2, jackHearts);
    addToColumn(column2, aceClubs);
    //SETUP FINISH

    /*
     *   TESTING
     */
    //normal move
    if (!(moveIsValid(jackHearts, column1, 0))) result++;
    //Moving ace to foundation
    if (!(moveIsValid(aceClubs, foundation, 1))) result++;
    //Testing moving king to empty column
    if (!(moveIsValid(kingHearts, column3, 0))) result++;
    //Testing Invalid moves
    if ((moveIsValid(kingHearts, column1,0))) result++;
    if ((moveIsValid(kingHearts, column2,0))) result++;

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

    return result;
}

/**
 * @author Philip Astrup Cramer
 */
int columnTest(){
    int result = 0;
    result += testAddToColumn();
    result += 10 * testAppendToColumn();
    result += 100 * testMoveCard();
    result += 1000 * testMoveIsValid();
    return result;
}