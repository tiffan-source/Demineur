#ifndef __GAME__H__
#define __GAME__H__

#include "plateau.h"
#include "lib.h"

void startGame();
void loadGame();
void game(Plateau *board);
void listeAction();
Plateau *placeFlag(int x, int y, Plateau *board);
Plateau *makeAction(Plateau *plateau);
Plateau *revealSquare(int x, int y, Plateau *plateau);
int countMinesAround(int x, int y, Plateau *plateau);
int checkForWin(Plateau *plateau);
int checkForLoose(Plateau *plateau);
void saveGame(Plateau *plateau);
void resolePlateau(Plateau *plateau);

#endif /* __GAME__H__ */
