/*  
 * COMP10002 Foundations of Algorithms Assignment 2, Semester 1, 2021
 * 
 * Full Name: Tanay Khandelwal      
 * Student Number: 1168569 
 * Date: 22nd May, 2021            
 */

/************ Importing packages ************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/********* Definitions of constants ***********/
#define WORDS_IN_DICTIONARY 100
#define NUMBER_OF_EQUAL_SIGNS 26 
#define NUMBER_OF_WORDS_IN_LETTER 22
#define POS_TAGS_LENGTH 25 // (5 tags * 4 words per tag) + (4 spaces) + (1 '\0') = 25
#define VARIATION_FORMS_LENGTH 105 //(4 forms * 25 letters) + (4 numbers) + (1 '\0') = 105

/********** Type definitions ***********/ 

typedef struct {
    char word[NUMBER_OF_WORDS_IN_LETTER];
    char pos_tags[POS_TAGS_LENGTH];
    char variation_forms[VARIATION_FORMS_LENGTH];
} word_t;

typedef word_t dictionary_t[WORDS_IN_DICTIONARY];


/*********8** Helper function headers *********/
void header(int stagenumber);
void printstage1(word_t one_word);
void printstage2(int numberofwords, float average_var_forms);

/************* Function headers ***********/
word_t stage1();
void stage2();


/*********** Stage 1 *****************/

word_t stage1() {
    word_t one_word; 
    scanf("%s", one_word.word);
    scanf("\n");

    scanf("%[^\n]s", one_word.pos_tags);
    scanf("\n");

    scanf("%[^\n]s", one_word.variation_forms);      
    scanf("\n");
    memmove(&one_word.variation_forms[0], &one_word.variation_forms[1], VARIATION_FORMS_LENGTH);
    return one_word;
}

/************** Stage 1 helper functions *************/   
void printstage1(word_t one_word) {
    header(1);
    printf("Word 0: %s\n", one_word.word); 
    printf("POS: %s\n", one_word.pos_tags); 
    printf("Form: %s\n", one_word.variation_forms);
} 

void header(int stagenumber) {
    for(int i = 0; i < NUMBER_OF_EQUAL_SIGNS; i++) {
        printf("=");
    }
    printf("Stage %d", stagenumber); 
    for(int i = 0; i < NUMBER_OF_EQUAL_SIGNS; i++) {
        printf("=");
    }
    printf("\n");

}

/***************** Stage 2 ****************/
void stage2() {
    dictionary_t dict; 
    int counter = 0;
    char ch;
    for(int i = 0; i < WORDS_IN_DICTIONARY; i++) {
        if((ch=getchar()) != '*') {
            dict[counter++] = stage1();
        }
        else
            break;
    }
    int number_of_variation_forms = 0;
    for(int i = 0; i < counter; i++){
        for(int j = 0; j < (int)strlen(dict[i].variation_forms); j++){
            if(isdigit((int)dict[i].variation_forms[j])) 
               number_of_variation_forms++;
               }
    }
    printstage1(dict[0]);
    printstage2(counter, (number_of_variation_forms*1.0/counter));
}


/************* Stage 2 helper function **************/
void printstage2(int number_of_words, float avg_var_forms) {
    header(2); 
    printf("Number of words: %d\n", number_of_words);
    printf("Average number of variation forms per word: %.2f\n", avg_var_forms);
}

/************** Main/driver function *************/
int main(int argc, char* argv[]) {
    stage2();
    return 0;
}