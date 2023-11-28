#ifndef __PLATEAU__H__
#define __PLATEAU__H__

#include "case.h"
#include "error.h"
#include "lib.h"

struct plateau
{
    int width;
    int height;
    Square **grid;
};

typedef struct plateau Plateau;

struct stackPlateau
{
    Plateau *plateau;
    struct stackPlateau *next;
};

typedef struct stackPlateau StackPlateau;


const StackPlateau *stackPlateauTop;

void pushPlateau(Plateau *plateau);
void popPlateau(Plateau *plateau);

Plateau *createPlateau(int width, int height);
void destroyPlateau(Plateau* board);


#endif /* __PLATEAU__H__ */