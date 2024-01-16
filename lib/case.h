#ifndef __CASE__H__
#define __CASE__H__

#include "lib.h"

enum {EMPTY, MINE, UNKNOWN};

struct square
{
    char state;
    int flag;
    int resolve;
};

typedef struct square Square;

#endif /* __CASE__H__ */
