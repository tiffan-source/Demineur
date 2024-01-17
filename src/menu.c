#include "menu.h"

void displayMenu()
{
	// system("clear");
	printf("DEMINEUR Menu\n");
	printf("Choisissez une option\n");

	printf("1) Nouvelle partie\n");
    printf("2) Charger une partie\n");
}

void menu()
{
	int select;

	displayMenu();

	// write it better without scanf

	scanf("%d", &select);

	switch (select)
	{
	case 1:
		startGame();
		break;

    case 2:
        loadGame();
        break;
    
	default:
		optionNotRecognized();
		break;
	}
}
