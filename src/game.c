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
    char* resultat = (char*)malloc(12 * sizeof(char));  // "xH:yM:zS\0" nécessite 12 caractères

    // Formater le résultat
    snprintf(resultat, 12, "%02dH:%02dM:%02dS", heures, minutes, secondesRestantes);

    return resultat;
}

void whatHappensAtEnd(Game *partie){
	char *tempsEcouleFormate = tempsEcoule(partie->duree);
	time(&partie->endTime);

	partie->duree = difftime(partie->endTime, partie->startTime);
	

	destroyGame(partie);

	printf("Vous avez mis %s secondes pour resoudre le plateau\n", tempsEcouleFormate);

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
	time_t start, end;
    Plateau *board = partie->board;
	
	

	time(&start);

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

		if (partie->state == ENDBYUSER)
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

	time(&(partie->startTime));
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