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

// function new head of a list initialization
struct field *list_init(){
    struct field *head = malloc(sizeof(struct field));
    head->field_number=0;
    head->snake = NULL;
    head->ladder=NULL;
    head->next = NULL;
    head->last_field=1;
    return head;
};

// adding field at the end of the list
struct field *add_new_field(struct field *head, int index, struct field *snake, struct field *ladder, int last){

    struct field *new_field = malloc(sizeof(struct field)); //pointer to new list_node
    new_field->next = NULL;
    new_field->field_number = index;
    new_field->snake = snake;
    new_field->ladder = ladder;
    new_field->last_field = last;

    // pointing to the head of the list
    struct field *cursor = head;
    // navigating to end of the list
    while(cursor->next != NULL){
        cursor = cursor->next;
    }
    //assign new node
    cursor->next = new_field;
    return new_field;
}

// function find node by it's field number
struct field *find_node_by_content(struct field *head, int value){
    struct field *cursor;

    cursor = head->next; // dont start at the head because head content is NULL

    // navigating through the list until it finds content = value
    while(cursor->field_number != value){
        if(cursor->next == NULL) {
            printf("Not in the list %d", value);
            return NULL; // value was not in the list
        }
        cursor = cursor->next;
    }
    return cursor;
}

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
                printf("Numbers of fields: %d\n", number_of_fields);
                // init head
                struct field *p_head = list_init();

                // create linked list and connect fields
                for(int i=1; i< number_of_fields; i++){
                    add_new_field(p_head,i,NULL,NULL,1);
                }
                // add last field to the board
                struct field *last_f = add_new_field(p_head,number_of_fields,NULL,NULL,0);

                // navigating through list
                struct field *cursor = p_head;
                while(cursor->last_field != 0) {
                    printf("field nr: %d\n", cursor->field_number);
                    cursor = cursor->next;
                }
                // print last field nr
                printf("field nr: %d\n", cursor->field_number);

                p_filed = find_node_by_content(p_head, 30);

                printf("field found: %d", p_filed->field_number);
                break;

            case '2':
                printf("Thank you, bye!\n");
                return 0;
        }
    }
    return 0;
}
