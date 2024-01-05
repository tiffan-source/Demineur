#include "../lib/game.h"

int countMinesAround(int x, int y, Plateau *plateau)
{

	return (1);
}

Plateau *revealSquare(int x, int y, Plateau *plateau)
{

	if (plateau->grid[y][x].state == MINE)
	{
		plateau->state = LOSE;
		return plateau;
	}

	int count = countMinesAround(x, y, plateau);


	return (plateau);
}

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

Plateau* placeFlag(int x, int y, Plateau* board)
{
	board->grid[y][x].flag = board->grid[y][x].flag ? 0 : 1;

	return (board);
}

/**
 * makeAction - apply some actions on the board
 * @board: the board to manipulate
 *
 * description: function to display, check, and apply
 * actions on @board
 * Return: the board
 */
Plateau *makeAction(Plateau *board)
{
	char action[5];

	printf("Entrez une action (x y action) et Q pour retourner au menu\n");

	fgets(action, 5, stdin);
	// lister les differentes tions possibles
	//listeAction();
	//clearBuff(); // clear out buffer input

	printf("action = %s\n", action);


	if (!checkCoord(action[1] - 'A', action[2] - '0', board) && action[0] != 'Q')
	{
		coordError();
		return (board);
	}

	switch (action[0])
	{
        case 'R':
		/* code */
		break;
        
        case 'F':
		board = placeFlag(action[1] - 'A', action[2] - '0', board);
		break;

        case 'Q':
		board->state = ENDBYUSER;
		break;

        default:
		break;
    }

	return (board);

}

void startGame()
{
	Plateau *board = createPlateau(9, 9);
	int endOfGame = 0;

	board = fillPlateauWithMine(board);

	clearBuff(); // skip the '\n' character of the user

	while (endOfGame == 0)
	{
		displayPlateau(board);

		board = makeAction(board);

		if (board->state == LOSE || board->state == ENDBYUSER || board->state == WIN)
		{
			endOfGame = 1;
		}        
	}

	destroyPlateau(board);
}

void listeAction()
{
	printf("Voici les differentes actions possibles");
	printf("A: ");
	printf("B: ");
}
