#include "game.h"


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

Plateau* revealSquare(int x, int y, Plateau *plateau)
{

    if (plateau->grid[y][x].state == MINE)
    {
        plateau->state = LOSE;
        return plateau;
    }

    if (plateau->grid[y][x].flag == 1)
    {
        return plateau;
    }

    int count = countMinesAround(x, y, plateau);
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

    return plateau;
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

	fflush(stdin); // clear out buffer input
	fgets(action, 5, stdin);
	// lister les differentes tions possibles
	//listeAction();

	printf("action = %s\n", action);


	if ((action[0] == 'F' || action[0] == 'R') && !checkCoord(action[1] - 'A', action[2] - '0', board))
	{
		coordError();
		return (board);
	}

	switch (action[0])
	{
        case 'R':
        board = revealSquare(action[1] - 'A', action[2] - '0', board);
        break;
        
        case 'F':
		board = placeFlag(action[1] - 'A', action[2] - '0', board);
		break;

        case 'Q':
		board->state = ENDBYUSER;
		break;

        case 'S':
        saveGame(board);
        board->state = ENDBYUSER;

        case 'T':
        resolePlateau(board);
        break;

        default:
		break;
    }

	return (board);
}

int checkForWin(Plateau *plateau){
    if (plateau->goalReveal == 0)
    {
        plateau->state = WIN;
        return 1;
    }
    return 0;
}

int checkForLoose(Plateau *plateau){
    if (plateau->state == LOSE)
    {
        return 1;
    }

    return 0;
    
}

void game(Plateau *board)
{
    
    int endOfGame = 0;
    time_t start, end;

    time(&start);

	while (endOfGame == 0)
	{
        board->state = INPROGRESS;

		displayPlateau(board);

		board = makeAction(board);
            
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

    displayPlateau(board);

    printf("Vous avez mis %d secondes pour resoudre le plateau\n", board->duree);

        sleep(2);


}


void startGame()
{
	Plateau *board = createPlateau();

	board = fillPlateauWithMine(board);

    game(board);

	destroyPlateau(board);
}

void saveGame(Plateau *plateau)
{

    char* pwd = getenv("PWD");
    char filePath[256];
    FILE* saveFile;

    sprintf(filePath, "%s/save.txt", pwd);

    saveFile = fopen(filePath, "a+");

    if (saveFile == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        exit(1);
    }

    fprintf(saveFile, "%d %d %d %d ", plateau->width, plateau->height, plateau->state, plateau->goalReveal);

    int i, j;

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

void listeAction()
{
	printf("Voici les differentes actions possibles");
	printf("A: ");
	printf("B: ");
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


    game(board);
    
    destroyPlateau(board);
}
