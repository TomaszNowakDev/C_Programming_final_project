#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// global variable declaration
FILE *f;

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

// function find node by it is field number
struct field *find_node_by_content(struct field *head, int value){
    struct field *cursor;

    cursor = head->next; // don't start at the head because head content is NULL

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

// function to roll a die
int roll_a_die(){
    int move = 0;
    move = (rand() % 6) +1;
    return move;
}

// function set snakes and ladders, takes: pointer to head, number of fields, number of snakes, number of ladders
void set_snakes_and_ladders(struct field *head, int number_of_fields, int snakes_number, int ladders_number) {

    int i = 0; // iterator for num snakes
    int j = 0; // iterator for num ladder
    while (i < snakes_number) {
        // snake's head and tail global declaration
        int snake_head;
        struct field *snake_head_find = NULL;
        struct field *snake_tail_find = NULL;

        // randomly generate number field to set snake's head
        // making sure that snake's head is not on the first or the last field
        snake_head = (rand() % (number_of_fields - 2)) + 2;
        snake_head_find = find_node_by_content(head, snake_head);
        if (snake_head_find->snake == NULL) { // making sure there is only one snake's head on selected square
            int snake_length = (rand() % 10) + 1; // randomly generate length of snake

            while ((snake_head - snake_length) <= 1) { // making sure that tail is in the board
                snake_head = (rand() % (number_of_fields - 2)) + 2;
                snake_head_find = find_node_by_content(head, snake_head);
            }
            // field previous to the field we want holds pointer to the filed we want
            int previous_field = snake_head - snake_length - 1;
            snake_tail_find = find_node_by_content(head, previous_field);
            snake_head_find->snake = snake_tail_find->next;
            printf("Snake set at field: %d\n", snake_head_find->field_number);
            fprintf(f,"Snake set at field: %d\n", snake_head_find->field_number);
            i++;
        } else {
            printf("There is Snake's head is on this field already!\n");
        }
    }
    // setting ladders
    while(j < ladders_number){
        int foot;
        struct field *ladder_foot_find = NULL;
        struct field *ladder_top = NULL;

        foot = (rand() % (number_of_fields - 2)) + 2; // making sure that ladder's foot is not on the first or the last field
        ladder_foot_find = find_node_by_content(head, foot);
        // making sure there is no snake's head or ladder's foot on selected field already
        if(ladder_foot_find->snake == NULL && ladder_foot_find->ladder == NULL){
            int ladder_length = (rand() % 10) +1; // randomly generate length of ladder

            while((foot + ladder_length) >= number_of_fields){ // making sure the top of the ladder is on the board
                foot = (rand() % (number_of_fields - 2)) + 2;
                ladder_foot_find = find_node_by_content(head, foot);
            }

            int ladder_end = foot + ladder_length -1; // field previous to the field we want holds pointer to the filed we want
            ladder_top = find_node_by_content(head, ladder_end);
            ladder_foot_find->ladder = ladder_top->next;
            printf("Ladder's foot set at field: %d\n", ladder_foot_find->field_number);
            fprintf(f,"Ladder's foot set at field: %d\n", ladder_foot_find->field_number);
            j++;
        } else{
            printf("There is ladder's foot or snake's head on this field already!\n");
        }
    }
}

// function play the game takes' pointer to the list head and number of fields on the board
void play_the_game(struct field *head, int number_of_fields){

    struct field *cursor = head; // cursor declaration to travel through the board
    int move;
    int fields_traveled = 0;
    while(cursor->next != NULL){

        move = roll_a_die();

        printf("\nYou rolled %d\n", move);
        fprintf(f,"\nYou rolled %d\n", move);
        if(number_of_fields < (fields_traveled + move)){
            printf("That's too much! there is less squares to the end of the board!\n");
            fprintf(f,"That's too much! there is less squares to the end of the board!\n");
            roll_a_die();
        } else {
            fields_traveled = fields_traveled + move;
            printf("Your position: %d, Number of fields: %d\n", fields_traveled, number_of_fields);
            fprintf(f,"Your position: %d, Number of fields: %d\n", fields_traveled, number_of_fields);
            for(int i = 0; i < move; i++){
                cursor = cursor->next;
            }
            printf("You are at field %d\n", cursor->field_number);
            fprintf(f,"You are at field %d\n", cursor->field_number);
        }

        if(cursor->snake != NULL){
            printf("This field is the head of a snake!\n");
            fprintf(f,"This field is the head of a snake!\n");
            cursor = cursor->snake;
            fields_traveled = cursor->field_number;
            printf("You slide down the snake, now you are at field %d\n", cursor->field_number);
            fprintf(f,"You slide down the snake, now you are at field %d\n", cursor->field_number);
        }

        if(cursor->ladder != NULL){
            printf("This field is the foot of a ladder!\n");
            fprintf(f,"This field is the foot of a ladder!\n");
            cursor = cursor->ladder;
            fields_traveled = cursor->field_number;
            printf("You are climbing the ladder, now you are at field %d\n", cursor->field_number);
            fprintf(f,"You are climbing the ladder, now you are at field %d\n", cursor->field_number);
        }
        printf("Press enter to continue");
        getchar();
    }
    printf("End of the game, You won!\n");
    fprintf(f,"\nEnd of the game, You won!\n");
}

void free_memory(struct field *head){
    // free memory allocated by malloc
    struct field *cursor;
    for(cursor = head->next; cursor != NULL; cursor = cursor->next){
        struct field *temp = cursor;
        cursor = cursor->next;
        free(temp);
    }
}

void print_all_fields(struct field *head){
    // navigating through list
    struct field *cursor = head;
    while(cursor->last_field != 0) {
        printf("field nr: %d\n", cursor->field_number);
        cursor = cursor->next;
    }
    // print last field nr
    printf("field nr: %d\n", cursor->field_number);

}

int main(int argc, char *argv[]){

    // declaring number of snakes and ladders for args from the command line
    int number_of_snakes = strtol(argv[1], NULL, 10);
    int number_of_ladders = strtol(argv[2], NULL, 10);

    // if number of arguments is 2 and the numbers of snakes and ladders are not too big
    if( argc == 3 && (number_of_snakes <= 5 || number_of_ladders <= 5)) {
        printf("The arguments supplied accepted!\n");

        srand(time(NULL));
        int number_of_fields;
        int upper = 64;
        int lower = 32;
        char option = '\0';
        struct field *p_filed = NULL;

        // opening file and error checking
        f = fopen("game_report.txt", "w");
        if(f == NULL){
            printf("Problem with this file, connection not established!\n");
            return 1;
        }

        printf("\n\t***********************************\n\t*                                 *\n\t*       Snakes and Ladders        *\n\t*                                 *\n\t***********************************\n");
        fprintf(f,"\n\t***********************************\n\t*                                 *\n\t*       Snakes and Ladders        *\n\t*                                 *\n\t***********************************\n");

        //main game loop
        while(1){
            printf("\nOptions:\n");
            printf("1. Start the game!\n2. Exit\n>>> ");
            option = getchar();
            getchar();

            switch(option){

                case '1':
                    number_of_fields = (rand() % (upper - lower + 1)) + lower; // random number of fields
                    printf("Numbers of fields: %d\n", number_of_fields);
                    fprintf(f,"Numbers of fields on the board: %d \n", number_of_fields);
                    printf("\nSnakes: %d Ladders: %d\n", number_of_snakes, number_of_ladders);
                    fprintf(f,"Snakes: %d Ladders: %d\n", number_of_snakes, number_of_ladders);
                    // init head
                    struct field *p_head = list_init();

                    // create linked list and connect fields
                    for(int i=1; i< number_of_fields; i++){
                        add_new_field(p_head,i,NULL,NULL,1);
                    }
                    // add last field to the board
                    struct field *last_f = add_new_field(p_head,number_of_fields,NULL,NULL,0);

                    set_snakes_and_ladders(p_head, number_of_fields, number_of_snakes, number_of_ladders);

                    printf("\nLet's start the game!\n");
                    fprintf(f,"\nLet's start the game!\n");

                    play_the_game(p_head, number_of_fields); // call the function to play the game

                    fclose(f); // close the file

                    // free_memory(p_head); // free memory allocated with malloc
                    break;

                case '2':
                    printf("Thank you, bye!\n");
                    return 0;
            }
        }
    }
}
