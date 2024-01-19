#include "menu.h"

/**
 * main - programm entry point
 *
 * Return: an int
 */

int main(void)
{
    int inGame = 1;

    while (inGame)
    {
	inGame = menu();
    }

	return (0);
}
