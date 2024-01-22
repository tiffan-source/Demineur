#include "plateau.h"


void setCustomePlateauSettings(int *width, int *height)
{
    char widthStr[256];
    char heightStr[256];

    int validWidth = 0;
    int validHeight = 0;

    while (!validWidth)
    {
        printf("Veuillez choisir la largeur du plateau de jeu (1-26) :\n");
        fgets(widthStr, 256, stdin);

        *width = atoi(widthStr);

        if (*width >= 1 && *width <= 26)
        {
            validWidth = 1;
        }
        else
        {
            printf("La largeur doit être comprise entre 1 et 26.\n");
        }
    }

    while (!validHeight)
    {
        printf("Veuillez choisir la hauteur du plateau de jeu (1-26) :\n");
        fgets(heightStr, 256, stdin);

        *height = atoi(heightStr);

        if (*height >= 1 && *height <= 26)
        {
            validHeight = 1;
        }
        else
        {
            printf("La hauteur doit être comprise entre 1 et 26.\n");
        }
    }
}

void setPlateauSettings(int *width, int *height)
{
	char choice[256];

	// system("clear");

	printf("\tVeuillez choisir la taille du plateau de jeu :\n");
	printf("\t1 - Petit (Defaut) (%dx%d)\n", DEFAULT_WIDTH, DEFAULT_HEIGHT);
	printf("\t2 - Moyen (16x16)\n");
	printf("\t3 - Grand (26x16)\n");
	printf("\t4 - Personnalisé\n");

	fgets(choice, 256, stdin);

    
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

	// system("clear");
	
    printf("  ");

	for (j = 0; j < plateau->width; j++)
	{
		printf(" %c ", j + 'A');
	}
	printf("\n");
    
	for (i = 0; i < plateau->height; i++)
	{
		for (j = 0; j < plateau->width; j++)
		{
			if (j == 0 ){
				if(i <= 9){
					printf(" %d", i);
				}
				else{
					printf("%d", i);
				}
			}
            
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
	printf("\n");
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
