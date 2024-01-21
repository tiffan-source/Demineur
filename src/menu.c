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
	printf("CHOISISSEZ VOTRE OPTION\n");
	printf("1) Nouvelle partie\n");
	printf("2) Charger une partie\n");
	printf("3) Quitter\n");
}

/**
 * menu - programm menu to be
 * displayed
 *
 * Return: an int element
 */
int menu()
{
	char select;

	displayMenu();

        scanf("%c", &select);
        clearBuff();

	switch (select)
	{
	case '1':
		startGame();
        return 1;
		break;

	case '2':
		loadGame();
		return (1);
		break;
    
        case '3':
		return (0);
		break;

	default:
		optionNotRecognized();
		return (1);
		break;
	}
}
