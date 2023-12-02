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
    }

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
            newPlateau->grid[i][j].state = EMPTY;
    }

    newPlateau->height = height;
    newPlateau->width = width;

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

    for (i = 0; i < plateau->height; i++)
    {
        for (j = 0; j < plateau->width; j++)
        {
            printf("| |");
            // show mine if it's a mine : just to test
            // if (plateau->grid[i][j].state == MINE)
            //     printf("|X|");
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