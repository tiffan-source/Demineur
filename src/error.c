#include "../lib/error.h"

/**
 * optionNotRecognized - Display an appropriate sentence
 * on unknown menue option
 *
 * Return: a type void element
 */
void optionNotRecognized()
{
	printf("Option not recognized\n");
	printf("Please try again\n");
}

/**
 * memoryError - Display an appropriate sentence
 * on memory error
 *
 * Return: a type void element
 */
void memoryError()
{
	printf("Memory error");
	exit(EXIT_FAILURE);
}

/**
 * coordError - Display an appropriate sentence
 * on coordonate errors
 *
 * Return: a type void element
 */
void coordError()
{
	printf("Invalid coordonate\n");
}

/**
 * clearBuff - discard properly possible remaining inputs
 * in buffer
 *
 * Return: a type void element
 */
void clearBuff()
{
	while (getchar() != '\n')
		continue;
}
