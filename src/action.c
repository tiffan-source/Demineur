#include "action.h"


/**
 * checkCoord - check board coordonates
 * @x: x coordonate
 * @y: y coordonate
 *
 * description: check board coordonate given by the user
 * Return: 1 if everything is ok, 0 otherwise
 */
int checkCoord(int x, int y, Plateau* board)
{
	if (x < 0 || x >= board->width || y < 0 || y >= board->height)
		return (0);
	return (1);
}


int countMinesAround(int x, int y, Plateau* plateau)
{
    int number = 0;

    // Coin superieur gauche
    if ((x - 1) >= 0 && (y - 1) >= 0 && plateau->grid[y - 1][x - 1].state == MINE)
    {
        number++;
    }

    // Haut
    if ((y - 1) >= 0 && plateau->grid[y - 1][x].state == MINE)
    {
        number++;
    }

    // Coin superieur droit
    if ((x + 1) < plateau->width && (y - 1) >= 0 && plateau->grid[y - 1][x + 1].state == MINE)
    {
        number++;
    }

    // Droite
    if ((x - 1) >= 0 && plateau->grid[y][x - 1].state == MINE)
    {
        number++;
    }

    // Gauche
    if ((x + 1) < plateau->width && plateau->grid[y][x + 1].state == MINE)
    {
        number++;
    }

    // Coin inferieur gauche
    if ((x - 1) >= 0 && (y + 1) < plateau->height && plateau->grid[y + 1][x - 1].state == MINE)
    {
        number++;
    }

    // Bas
    if ((y + 1) < plateau->height && plateau->grid[y + 1][x].state == MINE)
    {
        number++;
    }

    // Coin inferieur droit
    if ((x + 1) < plateau->width && (y + 1) < plateau->height && plateau->grid[y + 1][x + 1].state == MINE)
    {
        number++;
    }

    return number;
}



int revealSquare(int x, int y, Plateau *plateau)
{
	int count;

	if (plateau->grid[y][x].state == MINE)
	{
		// plateau->state = LOSE;
        return 0;
	}

	if (plateau->grid[y][x].flag == 1)
	{
		return 1;
	}

    count = countMinesAround(x, y, plateau);

	plateau->grid[y][x].state = '0' + count;
	plateau->goalReveal--;
	plateau->grid[y][x].resolve = 1;

	if (count == 0)
	{
        // Coin superieur gauche
		if ((x - 1) >= 0 && (y - 1) >= 0 && plateau->grid[y - 1][x - 1].resolve == 0)
        {
		revealSquare(x - 1, y - 1, plateau);
        }

		// Haut
		if ((y - 1) >= 0 && plateau->grid[y - 1][x].resolve == 0)
        {
		revealSquare(x, y - 1, plateau);
        }

		// Coin superieur droit
		if ((x + 1) < plateau->width && (y - 1) >= 0 && plateau->grid[y - 1][x + 1].resolve == 0)
		{
			revealSquare(x + 1, y - 1, plateau);
		}

		// Droite
		if ((x - 1) >= 0 && plateau->grid[y][x - 1].resolve == 0)
		{
			revealSquare(x - 1, y, plateau);
		}

		// Gauche
		if ((x + 1) < plateau->width && plateau->grid[y][x + 1].resolve == 0)
		{
			revealSquare(x + 1, y, plateau);
		}
		
		// Coin inferieur gauche
		if ((x - 1) >= 0 && (y + 1) < plateau->height && plateau->grid[y + 1][x - 1].resolve == 0)
		{
			revealSquare(x - 1, y + 1, plateau);
		}

		// Bas
		if ((y + 1) < plateau->height && plateau->grid[y + 1][x].resolve == 0)
		{
			revealSquare(x, y + 1, plateau);
		}

		// Coin inferieur droit
		if ((x + 1) < plateau->width && (y + 1) < plateau->height && plateau->grid[y + 1][x + 1].resolve == 0)
		{
			revealSquare(x + 1, y + 1, plateau);
		}
		
	}

	return 1;
}


void placeFlag(int x, int y, Plateau* board)
{
	board->grid[y][x].flag = board->grid[y][x].flag ? 0 : 1;
}


/**
 * makeAction - apply some actions on the board
 * @board: the board to manipulate
 *
 * description: function to display, check, and apply
 * actions on @board
 * Return: the board
 */
void makeAction(Game *partie)
{
	char action;
    char coord1;
    int coord2;
    int readResult;
	int revealSquareState;

	printf("Entrez une action (action X Y) ou Q pour retourner au menu\n");
	listeAction();
    // clearBuff();
	// fgets(action, 5, stdin);

    clearBuff();
    readResult = scanf("%c-%c-%d", &action, &coord1, &coord2);

    while (!(readResult == 3 || action == 'Q' || action == 'S' || action == 'T'))
    {
        clearBuff();
        printf("Entrez une action (action X Y) ou Q pour retourner au menu\n");
        listeAction();
        readResult = scanf("%c-%c-%d", &action, &coord1, &coord2);

    }
	clearBuff();
    
    Plateau *board = partie->board;

	
	if ((action == 'F' || action == 'R') && !checkCoord(coord1 - 'A', coord2, board))
	{
		coordError();
		return;
	}

	switch (action)
	{
        case 'R':
		revealSquareState = revealSquare(coord1 - 'A', coord2, board);
		if(revealSquareState == 0){
			partie->state = LOSE;
		}
        break;

        case 'F':
		placeFlag(coord1 - 'A', coord2, board);
		break;

        case 'Q':
		partie->state = ENDBYUSER;
		break;

        case 'S':
		saveGame(partie);
		partie->state = SAVE;

        case 'T':
		resolePlateau(board);
		break;

        default:
		optionNotRecognized();
		break;
	}
}


void resolePlateau(Plateau *plateau)
{
	int i, j;

	for (i = 0; i < plateau->height; i++)
	{
		for (j = 0; j < plateau->width; j++)
		{
			if (plateau->grid[i][j].state == MINE)
			{
				plateau->grid[i][j].flag = 1;
			}
		}
	}
}


/**
 * listeAction - list game differents possible actions
 *
 * Return: a type void element
 */
void listeAction()
{
	printf("Voici les differentes actions possibles\n");
	printf("R: Afficher le vrai contenu des cases\n");
	printf("F: Placer un Flag sur une case\n");
	printf("S: Sauvegarder le jeux dans un fichier\n");
	printf("T: Résoudre le jeux\n");
	printf("Q: Quitter la partie\n");

	printf("Exemple: ");

	printf("FC4\n");
}
