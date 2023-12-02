#include "game.h"

void startGame()
{
    Plateau *board = createPlateau(5, 5);
    int endOfGame = 0;
    char action[5];

    board = fillPlateauWithMine(board);


    while (endOfGame == 0)
    {
        displayPlateau(board);

        fgets(action, 4, stdin);

        endOfGame = 1;
    }

    destroyPlateau(board);
}
