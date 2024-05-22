#include "menu.h"

/**
 * displayMenu - a function to display the menu
 *
 * Return: a type void element
 */
void displayMenu()
{
	system("clear");
	printf("\n* DEMINEUR MENU\n");
	printf("\tCHOISISSEZ VOTRE OPTION\n");
	printf("\t1) Nouvelle partie\n");
	printf("\t2) Charger une partie\n");
	printf("\t3) Quitter\n");
    printf("\t4) Statistiques\n");
}

/**
 * menu - programm menu to be
 * displayed
 *
 * Return: an int element
 */
int menu()
{
	char select[256];

	displayMenu();

		// clearBuff();
        // scanf("%c", &select);
        // clearBuff();
		fgets(select, 256, stdin);

	switch (select[0])
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

    case '4':
        displayStats();
        return 1;
        break;

	default:
		optionNotRecognized();
		return (1);
		break;
	}
}
