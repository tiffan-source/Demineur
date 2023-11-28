#include "./lib/game.h"

void startGame()
{
    Plateau *board = createPlateau(5, 5);

    destroyPlateau(board);
}
