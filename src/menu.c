#include "menu.h"

/**
 * displayMenu - a function to display the menu
 *
 * Return: a type void element
 */
void displayMenu()
{
	system("clear");
	printf("DEMINEUR Menu\n");
	printf("Choisissez une option\n");

	printf("1) Nouvelle partie\n");
	printf("2) Charger une partie\n");
}

/**
 * menu - programm menu to be
 * displayed
 *
 * Return: a type void element
 */
void menu()
{
	int select;
	int keepGoing = 1;

	displayMenu();

	while(keepGoing)
	{
		scanf("%d", &select);
		clearBuff();

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
}
