#ifndef __GAME__H__
#define __GAME__H__

#include "plateau.h"
#include "lib.h"

struct Game
{
    Plateau *board;
    time_t startTime;
    time_t endTime;
    double duree;    
};

typedef struct Game Game;

void startGame();
void loadGame();
void game(Game *partie);
int checkForWin(Plateau *plateau);
int checkForLoose(Plateau *plateau);
void saveGame(Game *partie);
void destroyGame(Game *partie);

#endif /* __GAME__H__ */
