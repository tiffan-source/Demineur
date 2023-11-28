#include "plateau.h"

Plateau *createPlateau(int width, int height)
{
    StackSquare *stackSquareTop = NULL;
    Plateau* new = NULL;
    int i;

    new = (Plateau*) malloc(sizeof(Plateau));
    

    if (new == NULL)
        memoryError();

    new->grid = (Square**) malloc(sizeof(Square*) * height);

    if (new->grid == NULL)
    {
        free(new);
        memoryError();
    }

    for (i = 0; i < height; i++)
    {
        new->grid[i] = (Square*) malloc(sizeof(Square) * width);

        if (new->grid[i] == NULL)
        {
            deepFreeStackSquare(stackSquareTop);
            free(new->grid);
            free(new);
            memoryError();
        }

        stackPlateauTop = pushSquare(stackSquareTop, new->grid[i]);
    }

    freeStackSquare(stackSquareTop);

    new->height = height;
    new->width = width;

    return new;
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