#include "error.h"

void sizePlateauError()
{
    system("clear");
    printf("La longueur recquise est intraitable\n");
    printf("La taille maximale du plateu est de 99x99\n");
    printf("Veuillez réessayer\n");
    printf("TIPS: Les tailles negatives ne sont pas accepter\n");

    sleep(1);
}

/**
 * optionNotRecognized - Display an appropriate sentence
 * on unknown menue option
 *
 * Return: a type void element
 */
void optionNotRecognized()
{
    system("clear");
	printf("Option not recognized\n");
	printf("Please try again\n");
    sleep(1);
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
	exit(1);
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
