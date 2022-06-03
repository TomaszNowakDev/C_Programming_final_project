#include <stdio.h>

int main() {
    char option = '\0';
    //main game loop
    while(1){
        printf("\nOptions:\n");
        printf("1. Start the game!\n2. Exit\n>>> ");
        option = getchar();
        getchar();

        switch(option){


            case '1':
                printf("\nLet's start the game!\n");
                break;

            case '2':
                printf("Thank you, bye!\n");
                return 0;
        }
    }
    return 0;
}
