#ifndef __CASE__H__
#define __CASE__H__

struct square
{
    int data;
};

typedef struct square Square;

struct stackSquare
{
    Square *square;
    struct stackSquare *next;
};

typedef struct stackSquare StackSquare;

StackSquare* pushSquare(StackSquare* stack, Square *square);
void deepFreeStackSquare(StackSquare* stack);
void freeStackSquare(StackPlateau* stack);

#endif /* __CASE__H__ */
