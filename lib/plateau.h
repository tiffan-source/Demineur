#ifndef __PLATEAU__H__
#define __PLATEAU__H__

#include "case.h"
#include "error.h"
#include "lib.h"

#define DEFAULT_PERCENTAGE_OF_MINE 0.5

enum {INIT, INPROGRESS, WIN, LOSE, ENDBYUSER};

struct plateau
{
	int width;
	int height;
	int state;
    int goalReveal;
    int duree;
	Square **grid;
};

typedef struct plateau Plateau;

void pushPlateau(Plateau *plateau);
void popPlateau(Plateau *plateau);


Plateau *createPlateau(int width, int height);
Plateau *createPlateauFromSave(const char *saveLine);

Plateau *fillPlateauWithMine(Plateau *plateau);

void destroyPlateau(Plateau* board);
void displayPlateau(Plateau *plateau);


#endif /* __PLATEAU__H__ */
