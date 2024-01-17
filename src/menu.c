#include "menu.h"

/**
 * displayMenu 
 * description: Affiche le Menu du jeu
 * Return: Rien
 */
void displayMenu()
{
	system("clear");
	printf("DEMINEUR Menu\n");
	printf("Choisissez une option\n");

	printf("1) Nouvelle partie\n");
}

/**
 * menu 
 * description: choisit un élément du menu
 * Return: Rien
 */
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
    
	default:
		optionNotRecognized();
		break;
	}
}
