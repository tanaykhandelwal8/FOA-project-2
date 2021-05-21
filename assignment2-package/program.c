// imports
#include <stdio.h>
#include <string.h>
#include <ctype.h>


// #DEFINES
#define MAX_UNIQUE_WORDS 100
#define LOWERCASE_LETTERS 22
#define POS_TAGS 5
#define LETTERS_PER_POS_TAG 4
#define VARIATION_FORMS 4
#define VARIATION_FORM_LENGTH 25
#define NUMBER_OF_EQUAL_SIGNS 26

// TYPEDEFS

// FUNCTION PROTOTYPES
void function_header(int stagenumber);

// FUNCTIONS

void function_header(int stagenumber) {
    int i; 
    for(i = 0; i < NUMBER_OF_EQUAL_SIGNS; i++) {
        printf("=");
    }
    printf("Stage %d", stagenumber);
    for(i = 0; i < NUMBER_OF_EQUAL_SIGNS; i++) {
        printf("=");

    }
}

void stage1() {

}
 
// main
int main(int argc, char* argv[]) {
    function_header(5);
}