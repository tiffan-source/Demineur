#include "plateau.h"

/**
 * createPlateau - create a the board game
 * @height: the height of the board
 * @width: width of the board
 *
 * description: function to create and initilize a board game
 * Return: the newlly created board
 */
Plateau *createPlateau(int width, int height)
{
	Plateau *newPlateau = NULL;
	int i;
	int j;

	newPlateau = (Plateau *)malloc(sizeof(Plateau));

	if (newPlateau == NULL)
		memoryError();

	newPlateau->grid = (Square **)malloc(sizeof(Square *) * height);

	if (newPlateau->grid == NULL)
	{
		free(newPlateau);
		memoryError();
	}

	for (i = 0; i < height; i++)
	{
		newPlateau->grid[i] = (Square *)malloc(sizeof(Square) * width);

		if (newPlateau->grid[i] == NULL)
		{
			for (j = 0; j < i; j++)
			{
				free(newPlateau->grid[j]);
			}
			free(newPlateau->grid);
			free(newPlateau);
			memoryError();
		}

		for (j = 0; j < width; j++)
		{
			newPlateau->grid[i][j].state = EMPTY;
			newPlateau->grid[i][j].flag = 0;
		}
	}

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
			newPlateau->grid[i][j].state = EMPTY;
	}

	newPlateau->height = height;
	newPlateau->width = width;
	newPlateau->state = INIT;
    newPlateau->goalReveal = height * width;
    newPlateau->duree = 0;
	
	return (newPlateau);
}

/**
 * destroyPlateau - free the board
 * @board: the board to be freed
 *
 * description: function to free the board created
 * at the beginning
 * Return: a type void element
 */
void destroyPlateau(Plateau* board)
{
	int i;

	for (i = 0; i < board->height; i++)
	{
		free(board->grid[i]);
	}

	free(board->grid);

	free(board);
}

// Ajouter balisage de la grille

/**
 * displayPlateau - display the board 
 * @plateau: the board to be displayed
 *
 * description: display the current board with its state
 * Return: a type void
 */
void displayPlateau(Plateau *plateau)
{
	int i;
	int j;

	// system("clear");

	printf(" ");
	for (j = 0; j < plateau->width; j++)
	{
		printf(" %c ", j + 'A');
	}
	printf("\n");
    
	for (i = 0; i < plateau->height; i++)
	{
		for (j = 0; j < plateau->width; j++)
		{
			if (j == 0)
				printf("%d", i);
            
            if (plateau->grid[i][j].flag)
            {
                printf("|F|");
            }
            else
            {
                if (plateau->grid[i][j].state == EMPTY || plateau->grid[i][j].state == MINE)
                {
                    printf("| |");
                }
                else
                {
                    printf("|%c|", plateau->grid[i][j].state);
                }
            }
        }
        printf("\n");
    }
}

/**
 * fillPlateauWithMine - fill the board with mines
 * @plateau: the board to be filled
 *
 * description: fill random squares of the board with mines 
 * Return: the filled board
 */
Plateau *fillPlateauWithMine(Plateau *plateau)
{
	int numberOfMine = (int) (plateau->width * plateau->height * DEFAULT_PERCENTAGE_OF_MINE);
	int i, x, y;

	srand(time(NULL));

	for (i = 0; i < numberOfMine; i++)
	{
		do
		{
			x = rand() % plateau->width;
			y = rand() % plateau->height;

		} while (plateau->grid[y][x].state == MINE);

		plateau->grid[y][x].state = MINE;
	}

    plateau->goalReveal -= numberOfMine;

	return (plateau);
}
