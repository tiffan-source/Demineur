#include "menu.h"

void displayMenu(){
    system("clear");
    printf("DEMINEUR Menu\n");
    printf("Choisissez une option\n");

    printf("1) Nouvelle partie\n");
}

void menu(){
    int select;

    displayMenu();

    scanf("%d", &select);

    switch (select)
    {
    case 1:
        startGame();
        break;
    
    default:
        optionNotRecognized();
        break;
    }
}