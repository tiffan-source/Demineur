#include "error.h"

void optionNotRecognized(){
    printf("Option not recognized\n");
}

void memoryError(){
    printf("Memory error");
    exit(EXIT_FAILURE);
}

void coordError(){
    printf("Coordonate invalide\n");
}