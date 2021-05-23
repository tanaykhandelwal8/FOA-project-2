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
#include <assert.h>

/********* Definitions of constants ***********/
#define WORDS_IN_DICTIONARY 100
#define NUMBER_OF_EQUAL_SIGNS 26
#define NUMBER_OF_WORDS_IN_LETTER 22
#define POS_TAGS_LENGTH 25         // (5 tags * 4 words per tag) + (4 spaces) + (1 '\0') = 25
#define VARIATION_FORMS_LENGTH 105 //(4 forms * 25 letters) + (4 numbers) + (1 '\0') = 105
#define WORDS_IN_SENTENCE_LENGTH 25

/********** Type definitions ***********/

typedef struct
{
    char word[NUMBER_OF_WORDS_IN_LETTER];
    char pos_tags[POS_TAGS_LENGTH];
    char variation_forms[VARIATION_FORMS_LENGTH];
} word_t;

typedef struct {
    char word[NUMBER_OF_WORDS_IN_LETTER];
    char pos_tags[POS_TAGS_LENGTH];
} stage3_t;

typedef word_t dictionary_t[WORDS_IN_DICTIONARY];

typedef char data_t[WORDS_IN_SENTENCE_LENGTH];
typedef struct node node_t;

struct node
{
    data_t data;
    node_t *next;
};

typedef struct
{
    node_t *head;
    node_t *foot;
} list_t;

/*********8** Helper function headers *********/
// Stage 1
void header(int stagenumber);
void printstage1(word_t one_word);

// Stage 2
void printstage2(int numberofwords, float average_var_forms);

// Stage 3
list_t *create_empty_list();
void push(list_t *mylist, data_t new_item);
void print_list(list_t *mylist);
void free_list(list_t *mylist);
int getword(char W[], int limit);
data_t* get_head(list_t *list);
int binary_search(dictionary_t dict, data_t word, int upper_bound);
/************* Function headers ***********/
word_t stage1();
int stage2(dictionary_t dict);
void stage3(dictionary_t dict);
void stage4(dictionary_t dict);

/*********** Stage 1 *****************/

word_t stage1()
{
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
void printstage1(word_t one_word)
{
    header(1);
    printf("Word 0: %s\n", one_word.word);
    printf("POS: %s\n", one_word.pos_tags);
    printf("Form: %s\n", one_word.variation_forms);
}

void header(int stagenumber)
{
    for (int i = 0; i < NUMBER_OF_EQUAL_SIGNS; i++)
    {
        printf("=");
    }
    printf("Stage %d", stagenumber);
    for (int i = 0; i < NUMBER_OF_EQUAL_SIGNS; i++)
    {
        printf("=");
    }
    printf("\n");
}

/***************** Stage 2 ****************/
int stage2(dictionary_t dict)
{
    char ch;
    int counter = 0;
    for (int i = 0; i < WORDS_IN_DICTIONARY; i++)
    {
        if ((ch = getchar()) != '*')
        {
            dict[counter++] = stage1();
        }
        else
            break;
    }
    int number_of_variation_forms = 0;
    for (int i = 0; i < counter; i++)
    {
        for (int j = 0; j < (int)strlen(dict[i].variation_forms); j++)
        {
            if (isdigit((int)dict[i].variation_forms[j]))
                number_of_variation_forms++;
        }
    }
    printstage1(dict[0]);
    printstage2(counter, (number_of_variation_forms * 1.0 / (counter)));

    return counter;
}

/************* Stage 2 helper function **************/
void printstage2(int number_of_words, float avg_var_forms)
{
    header(2);
    printf("Number of words: %d\n", number_of_words);
    printf("Average number of variation forms per word: %.2f\n", avg_var_forms);
}

/*********** Stage 3 ***********************/

void stage3(dictionary_t dict)
{
    int counter = stage2(dict);
    list_t *words_in_sentence = create_empty_list();
    data_t word;
    int length_of_sentence = 0;
    //creating the linked list using functions taken from get_n_prime.c
    int a; // variable to check whether the function getword() has reached EOF
    while((a=getword(word, WORDS_IN_SENTENCE_LENGTH)) != EOF) {
        push(words_in_sentence, word);
        length_of_sentence++;
    }
    int count=0;
    stage3_t tags[length_of_sentence];
    node_t* temp = words_in_sentence->head;
    while(temp != NULL) {
        int location;
        if((location=binary_search(dict, temp->data, counter))) {
            strcpy(tags[count].word,temp->data);
            strcpy(tags[count++].pos_tags,dict[location].pos_tags);
        }
        else {
            strcpy(tags[count].word, temp->data);
            strcpy(tags[count++].pos_tags, "NOT_FOUND");
        }
        temp = temp->next;
    }
    header(3);
    for(int i = 0; i < length_of_sentence; i++) {
        printf("%s\t\t%-12s\n", tags[i].word, tags[i].pos_tags);
    }

}


/******* Stage 3 Helper functions ***********/
int binary_search(dictionary_t dict, data_t word, int upper_bound) {
        int bottom = 0; 
        int top = upper_bound; 
        int mid; 
        while(bottom <= top) {
            mid = (top+bottom)/2;

            if(strcmp(dict[mid].word, word) == 0) {
                return mid;
            }
            else if(strcmp(dict[mid].word, word) > 0) {
                bottom = mid + 1;
            }
            else {
                top = mid - 1;
            }
            
        }
        return 0;
}
list_t *create_empty_list()
{
    list_t *mylist = (list_t *)malloc(1 * sizeof(list_t));
    assert(mylist);
    mylist->head = mylist->foot = NULL;
    return mylist;
}

void push(list_t *mylist, data_t new_item) {
	node_t *new = (node_t *)malloc(1*sizeof(node_t));
				
	if (new == NULL) {
		printf("Error!");
		exit(EXIT_FAILURE);
	}	
    strcpy(new->data, new_item);
	new->next = NULL;
		
	if (mylist->head == NULL) {
		mylist->head = mylist->foot = new;

	} else {
		mylist->foot->next = new;
		mylist->foot = new;	
	}
}

data_t* get_head(list_t *list) {
	assert(list!=NULL && list->head!=NULL);
	return &(list->head->data);
}

void print_list(list_t *mylist) {
	if(mylist->head) {
		node_t *new = mylist->head;

		while(new) {
			printf("%s ", new->data);
			new = new->next;
		}
		printf("\n");
	}
}

int getword(char W[], int limit)
{
    int c, len = 0;
    /* first, skip over any non alphabetics */
    while ((c = getchar()) != EOF && !isalpha(c))
    {
        /* do nothing more */
    }
    if (c == EOF)
    {
        return EOF;
    }
    /* ok, first character of next word has been found */
    W[len++] = c;
    while (len < limit && (c = getchar()) != EOF && isalpha(c))
    {
        /* another character to be stored */
        W[len++] = c;
    }
    /* now close off the string */
    W[len] = '\0';
    return 0;
}

/*************** Stage 4 ********************/
void stage4(dictionary_t dict) {


}
/************** Main/driver function *************/
int main(int argc, char *argv[])
{
    dictionary_t dict_of_words;
    stage3(dict_of_words);
    
    return 0;
}