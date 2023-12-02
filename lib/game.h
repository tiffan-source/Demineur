#ifndef __GAME__H__
#define __GAME__H__

#include "plateau.h"
#include "lib.h"

void startGame();

Plateau* makeAction(Plateau *plateau, char *action);


#endif /* __GAME__H__ */