#include "game.h"
#include "action.h"


/**
 * checkForWin - check whether the player won
 * @plateau: the argument
 *
 * Return: an int type
 */
int checkForWin(Plateau *plateau)
{
	if (plateau->goalReveal == 0)
	{
		plateau->state = WIN;
		return (1);
	}
	return (0);
}

/**
 * checkForLoose - check whether the player lost
 * @plateau: the entire game
 *
 * Return: an int type
 */
int checkForLoose(Plateau *plateau)
{
	if (plateau->state == LOSE)
	{
		return (1);
	}

	return (0);

}

/**
 * game - function to complete several actions
 * @board: to be filled
 *
 * description: this function lets user perfoms actions on the board
 * checks for user's win state, display board accordingly.
 * Return: a type void element
 */
void game(Game *partie)
{    
	int endOfGame = 0;
	time_t start, end;
    Plateau *board = partie->board;
	
	

	time(&start);

	while (endOfGame == 0)
	{
		board->state = INPROGRESS;

		displayPlateau(board);

		makeAction(partie);

		if (checkForWin(board))
		{
			displayPlateau(board);
			printf("Vous avez gagne\n");
			endOfGame = 1;
		}

		if (checkForLoose(board))
		{
			displayPlateau(board);
			printf("Vous avez perdu\n");
			endOfGame = 1;
		}

		if (board->state == ENDBYUSER)
		{
			endOfGame = 1;
		}
	}

	time(&end);

	board->duree = difftime(end, start);

	destroyGame(partie);

	printf("Vous avez mis %f secondes pour resoudre le plateau\n", board->duree);

    sleep(2);
}

/**
 * startGame - start the game
 *
 * Return: a type void element
 */
void startGame()
{

    Game *newGame = malloc(sizeof(Game));

    if (newGame == NULL)
    {
        memoryError();
    }
    
	Plateau *board = createPlateau();
	board = fillPlateauWithMine(board);

    newGame->board = board;

    game(newGame);

}

void saveGame(Game *partie)
{

	char *pwd = getenv("PWD");
	char filePath[256];
	FILE *saveFile;
	int i, j;
    Plateau *plateau = partie->board;

	sprintf(filePath, "%s/save.txt", pwd);

	saveFile = fopen(filePath, "a+");

	if (saveFile == NULL)
	{
		printf("Erreur lors de l'ouverture du fichier\n");
		exit(1);
	}

	fprintf(saveFile, "%d %d %d %d ", plateau->width, plateau->height, plateau->state, plateau->goalReveal);
    
	for (i = 0; i < plateau->height; i++)
	{
		for (j = 0; j < plateau->width; j++)
		{
			if (plateau->grid[i][j].state == MINE)
			{
				fprintf(saveFile, "M");
				if (plateau->grid[i][j].flag)
				{
					fprintf(saveFile, "F");
				}
				else{
					fprintf(saveFile, "_");
				}
			}
			else if (plateau->grid[i][j].flag == 1)
			{
				fprintf(saveFile, "F_");
			}
			else if (plateau->grid[i][j].state == EMPTY)
			{
				fprintf(saveFile, "__");
			}
			else
			{
				fprintf(saveFile, "%c_", plateau->grid[i][j].state);
			}
		}
	}
	fprintf(saveFile, "\n");
	fclose(saveFile);
}


int selectGame()
{
	FILE *save = NULL;
	char *line = NULL;
	int read;
	size_t len;
	int i = 0, toReveal, w, h, s, select;

	printf("Choisissez une partie a charger\n");

	char* pwd = getenv("PWD");
	char filePath[256];

	sprintf(filePath, "%s/save.txt", pwd);

	save = fopen(filePath, "r");

	if (save == NULL)
	{
		printf("Aucune sauvegarde disponible\n");
		exit(1);
	}

	while ((read = getline(&line, &len, save)) != -1)
	{
		sscanf(line, "%d %d %d %d", &w, &h, &s, &toReveal);
		i++;

		printf("%d) Partie %d Largeur: %d Hauteur: %d Etat: %d Case a reveler %d\n", i, i, w, h, s, toReveal);
	}

	if (line)
	{
		free(line);
	}


	if (i == 0)
	{
		printf("Aucune sauvegarde disponible\n");
		exit(1);
	}

	do
	{
		scanf("%d", &select);
		if (select < 1 || select > i)
		{
			printf("Veuillez entrer un nombre entre 1 et %d\n", i);
		}

	} while (select < 1 || select > i);


	fclose(save);

	return select;
}


void loadGame()
{
	int select = selectGame();
	FILE *save = NULL;
	char *line = NULL;
	size_t len;
	int read, i = 0;
	char* pwd = getenv("PWD");
	char filePath[256];
	Plateau* board;
    Game *partie = malloc(sizeof(Game));

    if (partie == NULL)
    {
        memoryError();
    }
    

	sprintf(filePath, "%s/save.txt", pwd);

	save = fopen(filePath, "r");

	if (save == NULL)
	{
		printf("Aucune sauvegarde disponible\n");
		exit(1);
	}

	while ((read = getline(&line, &len, save)) != -1)
	{
		i++;
		if (i == select)
		{
			board = createPlateauFromSave(line);
			free(line);
			fclose(save);
			break;
		}
	}

    partie->board = board;
	

	game(partie);

	
}

void destroyGame(Game *partie)
{
    destroyPlateau(partie->board);
    free(partie);
}