#include "plateau.h"

Plateau *createPlateau(int width, int height)
{
    Plateau* newPlateau = NULL;
    int i;
    int j;

    newPlateau = (Plateau*) malloc(sizeof(Plateau));

    if (newPlateau == NULL)
        memoryError();

    newPlateau->grid = (Square**) malloc(sizeof(Square*) * height);

    if (newPlateau->grid == NULL)
    {
        free(newPlateau);
        memoryError();
    }

    for (i = 0; i < height; i++)
    {
        newPlateau->grid[i] = (Square*) malloc(sizeof(Square) * width);

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

    return newPlateau;
}

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

void displayPlateau(Plateau *plateau)
{
    int i;
    int j;

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
            switch (plateau->grid[i][j].state)
            {
                case EMPTY:
                default:
                    printf("| |");
                    break;
            }
        }
        printf("\n");
    }
}

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

    return plateau;
}