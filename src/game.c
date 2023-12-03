#include "game.h"

int countMinesAround(x, y, plateau){

}

Plateau* revealSquare(int x, int y, Plateau *plateau)
{

    if (plateau->grid[y][x].state == MINE)
    {
        plateau->state = LOSE;
        return plateau;
    }

    int count = countMinesAround(x, y, plateau);


    return plateau;
}

int checkCoord(int x, int y, Plateau* board)
{
    if (x < 0 || x >= board->width || y < 0 || y >= board->height)
        return 0;
    return 1;
}

Plateau* placeFlag(int x, int y, Plateau* board)
{
    board->grid[y][x].flag = board->grid[y][x].flag ? 0 : 1;
    return board;
}

Plateau* makeAction(Plateau* board)
{
    char action[5];

    printf("Entrez une action (x y action) et Q pour retourner au menu\n");

    fgets(action, 5, stdin);

    printf("action = %s\n", action);

    if (!checkCoord(action[1] - 'A', action[2] - '0', board) && action[0] != 'Q')
    {
        coordError();
        return board;
    }

    switch (action[0])
    {
        case 'R':
            /* code */
            break;
        
        case 'F':
            board = placeFlag(action[1] - 'A', action[2] - '0', board);
            break;

        case 'Q':
            board->state = ENDBYUSER;
            break;

        default:
            break;
    }

    return board;

}

void startGame()
{
    Plateau *board = createPlateau(9, 9);
    int endOfGame = 0;

    board = fillPlateauWithMine(board);

    getchar();
    while (endOfGame == 0)
    {
        displayPlateau(board);

        board = makeAction(board);

        if (board->state == LOSE || board->state == ENDBYUSER || board->state == WIN)
        {
            endOfGame = 1;
        }        
    }

    destroyPlateau(board);
}
