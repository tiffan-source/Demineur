#ifndef __GAME__H__
#define __GAME__H__

#include "plateau.h"
#include "lib.h"


enum {INIT, INPROGRESS, WIN, LOSE, ENDBYUSER, SAVE};

struct Game
{
    Plateau *board;
    int state;
    time_t startTime;
    time_t endTime;
    double duree;
    char namePlayer[256]; 
};

typedef struct Game Game;

void startGame();
void loadGame();
void game(Game *partie);
int checkForWin(Game *partie);
int checkForLoose(Game *partie);
void saveGame(Game *partie);
void destroyGame(Game *partie);
Game *createGameFromSave(const char *saveLine);
void displayStats();


#endif /* __GAME__H__ */
