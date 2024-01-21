#ifndef __ACTION_H__
#define __ACTION_H__

#include "lib.h"
#include "game.h"
#include "plateau.h"

int checkCoord(int x, int y, Plateau *board);
void placeFlag(int x, int y, Plateau *board);
void makeAction(Game *partie);
void revealSquare(int x, int y, Plateau *plateau);
void resolePlateau(Plateau *plateau);
int countMinesAround(int x, int y, Plateau *plateau);
void listeAction();


#endif // __ACTION_H__