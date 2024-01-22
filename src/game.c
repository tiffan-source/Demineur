#include "game.h"
#include "action.h"


/**
 * checkForWin - check whether the player won
 * @plateau: the argument
 *
 * Return: an int type
 */
int checkForWin(Game *partie)
{
	if (partie->board->goalReveal == 0)
	{
		partie->state = WIN;
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
int checkForLoose(Game *partie)
{
	if (partie->state == LOSE)
	{
		return (1);
	}
	return (0);

}

char* tempsEcoule(double secondes) {
    int heures, minutes, secondesRestantes;
    
    heures = (int)(secondes / 3600);
    minutes = ((int)secondes % 3600) / 60;
    secondesRestantes = (int)secondes % 60;

    // Allouer une chaîne de caractères pour stocker le résultat
    char* resultat = (char*)malloc(24 * sizeof(char));  // "xH:yM:zS\0" nécessite 12 caractères

    // Formater le résultat
    snprintf(resultat, 24, "%02dh:%02dm:%02ds", heures, minutes, secondesRestantes);

    return resultat;
}

void whatHappensAtEnd(Game *partie){
	char *tempsEcouleFormate;
	time(&(partie->endTime));

	partie->duree += difftime(partie->endTime, partie->startTime);
	tempsEcouleFormate = tempsEcoule(partie->duree);

	destroyGame(partie);

    if (partie->state == WIN)
    {
        printf("Vous avez gagne en %s\n", tempsEcouleFormate);
    }
    else if (partie->state == LOSE)
    {
        printf("Vous avez perdu apres %s\n", tempsEcouleFormate);
    }
    else if (partie->state == SAVE)
    {
        printf("Partie sauvegardee\n");
    }
    else if (partie->state == ENDBYUSER)
    {
        printf("Partie terminee par l'utilisateur\n");
    }
    
    

	free(tempsEcouleFormate);

    sleep(2);
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
    Plateau *board = partie->board;
	
	time(&(partie->startTime));

	while (endOfGame == 0)
	{
		partie->state = INPROGRESS;

		displayPlateau(board);

		makeAction(partie);

		if (checkForWin(partie))
		{
			displayPlateau(board);
			endOfGame = 1;
		}

		if (checkForLoose(partie))
		{
			displayPlateau(board);
			endOfGame = 1;
		}

		if (partie->state == ENDBYUSER || partie->state == SAVE)
		{
			endOfGame = 1;
		}
	}

	whatHappensAtEnd(partie);
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

	time(&(newGame->startTime));
    newGame->duree = 0;
    
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

	time(&(partie->endTime));
	partie->duree = difftime(partie->endTime, partie->startTime);

	sprintf(filePath, "%s/save.txt", pwd);

	saveFile = fopen(filePath, "a+");

	if (saveFile == NULL)
	{
		printf("Erreur lors de l'ouverture du fichier\n");
		exit(1);
	}

	fprintf(saveFile, "%d %d %d %f ", plateau->width, plateau->height, plateau->goalReveal, partie->duree);
    
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

	partie->state = SAVE;
}


int selectGame()
{
	FILE *save = NULL;
	char *line = NULL;
	int read;
	size_t len;
	int i = 0, toReveal, w, h, s;
    char select[256];

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
        fgets(select, 256, stdin);
		if (atoi(select) < '1' || atoi(select) > i)
		{
			printf("Veuillez entrer un nombre entre 1 et %d\n", i);
		}

	} while (atoi(select) < 1 || atoi(select) > i);


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
    Game *partie = NULL;


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
			partie = createGameFromSave(line);
			free(line);
			fclose(save);
			break;
		}
    }

    time(&(partie->startTime));

	game(partie);
	
}

void destroyGame(Game *partie)
{
    destroyPlateau(partie->board);
    free(partie);
}


/**
 * createPlateauFromSave - create a the board from the save one
 * @saveLine: the line which contains the saved game information
 *
 * description: function to create and print out the last board game
 * Return: the saved game board
 */
Game *createGameFromSave(const char *saveLine)
{
    Game *newGame = NULL;
	Plateau *newPlateau = NULL;
	int i, j, testAssign;
	int width, height, state, goal;
    double duree;
	char caseData[2048];


    newGame = (Game *)malloc(sizeof(Game));

    if (newGame == NULL)
    {
        memoryError();
    }

	newPlateau = (Plateau*) malloc(sizeof(Plateau));

	if (newPlateau == NULL)
		memoryError();

	testAssign = sscanf(saveLine, "%d %d %d %lf %s", &width, &height, &goal, &duree, caseData);

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
                if (caseData[width*i*2+2*j] == 'F')
                {
                    newPlateau->grid[i][j].flag = 1;
                }
                else
                {
                    newPlateau->grid[i][j].state = caseData[width*i*2+2*j];
                }
			}
		}
	}

	newPlateau->height = height;
	newPlateau->width = width;
	newPlateau->goalReveal = goal;

    newGame->board = newPlateau;
    newGame->state = INPROGRESS;
    newGame->duree = duree;

    return (newGame);
}
