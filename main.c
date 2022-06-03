#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// define field struct
struct field{
    int field_number;
    struct field *snake;
    struct field *ladder;
    struct field *next;
    int last_field; // if the last_field value is 1, this is not the last field. if 0 it is last field
};

int main() {
    srand(time(NULL));
    int number_of_fields;
    int upper = 64;
    int lower = 32;
    char option = '\0';
    struct field *p_filed = NULL;

    //main game loop
    while(1){
        printf("\nOptions:\n");
        printf("1. Start the game!\n2. Exit\n>>> ");
        option = getchar();
        getchar();

        switch(option){

            case '1':
                printf("\nLet's start the game!\n");
                number_of_fields = (rand() % (upper - lower + 1)) + lower; // random number of fields
                printf("Numbers of fields: %d", number_of_fields);
                break;

            case '2':
                printf("Thank you, bye!\n");
                return 0;
        }
    }
    return 0;
}
