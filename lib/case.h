#ifndef __CASE__H__
#define __CASE__H__

#include "lib.h"

enum {EMPTY, MINE, FLAG, UNKNOWN};

struct square
{
    char state;
};

typedef struct square Square;

#endif /* __CASE__H__ */
