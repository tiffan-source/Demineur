#include "plateau.h"


void setCustomePlateauSettings(int *width, int *height)
{
	int choiceWidth;
	int choiceHeight;

	system("clear");

	printf("Veuillez choisir la taille du plateau de jeu :\n");

	while (scanf("%d", &choiceWidth) != 1 || choiceWidth < 1 || choiceWidth > 26)
	{
		printf("Veuillez choisir la largeur du plateau de jeu (1-26) :\n");
		clearBuff(); /** clear out buffer */
	}

	while (scanf("%d", &choiceHeight) != 1 || choiceHeight < 1 || choiceHeight > 26)
	{
		printf("Veuillez choisir la hauteur du plateau de jeu (1-26) :\n");
		clearBuff();  /** clear out buffer */
	}
	
	*width = choiceWidth;
	*height = choiceHeight;
}

void setPlateauSettings(int *width, int *height)
{
	char choice[256];

	system("clear");

	printf("Veuillez choisir la taille du plateau de jeu :\n");
	printf("1 - Petit (Defaut) (%dx%d)\n", DEFAULT_WIDTH, DEFAULT_HEIGHT);
	printf("2 - Moyen (16x16)\n");
	printf("3 - Grand (26x16)\n");
	printf("4 - Personnalisé\n");

	scanf("%s", choice);
	if (strlen(choice) > 1)
	{
		optionNotRecognized();
		setPlateauSettings(width, height);
		return;
	}
    

	switch (choice[0])
	{
        case '1':
		*width = DEFAULT_WIDTH;
		*height = DEFAULT_HEIGHT;
		break;
        case '2':
		*width = 16;
		*height = 16;
		break;
        case '3':
		*width = 26;
		*height = 16;
		break;
        case '4':
		setCustomePlateauSettings(width, height);
		break;

        default:
		optionNotRecognized();
		setPlateauSettings(width, height);
		break;
	}
	
}

/**
 * createPlateau - create a the board game
 * 
 * description: function to create and initilize a board game
 * Return: the newlly created board
 */
Plateau *createPlateau()
{
	Plateau *newPlateau = NULL;
	int i;
	int j;
	int height = DEFAULT_HEIGHT;
	int width = DEFAULT_WIDTH;

	setPlateauSettings(&width, &height);

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
void destroyPlateau(Plateau *board)
{
	int i;

	for (i = 0; i < board->height; i++)
	{
		free(board->grid[i]);
	}

	free(board->grid);

	free(board);
}


/**
 * displayPlateau - display the board 
 * @plateau: the board to be displayed
 *
 * description: display the current board with its state
 * Return: a type void
 */
void displayPlateau(Plateau *plateau)
{
	int i, j;

	system("clear");
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

/**
 * createPlateauFromSave - create a the board from the save one
 * @saveLine: the line which contains the saved game information
 *
 * description: function to create and print out the last board game
 * Return: the saved game board
 */
Plateau *createPlateauFromSave(const char *saveLine)
{
	Plateau *newPlateau = NULL;
	int i, j, testAssign;
	int width, height, state, goal;
	char caseData[256];

	newPlateau = (Plateau*) malloc(sizeof(Plateau));

	if (newPlateau == NULL)
		memoryError();

	testAssign = sscanf(saveLine, "%d %d %d %d %s", &width, &height, &state, &goal, caseData);

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
		{
			if (caseData[width * i * 2 + 2 * j] == 'M')
			{
				newPlateau->grid[i][j].state = MINE;
				newPlateau->grid[i][j].flag = caseData[width*i*2+2*j + 1] == 'F' ? 1 : 0;
			}
			else if(caseData[width * i * 2 + 2 * j] != '_')
			{
				newPlateau->grid[i][j].state = caseData[width*i*2+2*j];
			}
		}
	}

	newPlateau->height = height;
	newPlateau->width = width;
	newPlateau->state = INPROGRESS;
	newPlateau->goalReveal = goal;

	return (newPlateau);
}
