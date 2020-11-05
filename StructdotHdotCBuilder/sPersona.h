#ifndef SPERSONA_H_INCLUDED
#define SPERSONA_H_INCLUDED
#include "LinkedList.h"

typedef struct{
    int id;
}sPersona;

#endif // The program that made this file (and it's c partner) was made by Plain_Sight

// Comparers, Getters, Setters

int per_comId(void* persona1, void* persona2);
int per_getId(sPersona* persona, int* id);
int per_setId(sPersona* persona, int id);

// Basic Struct Functions

void per_show(sPersona* persona);
int per_showAll(LinkedList* this, char* errorMesage);


sPersona* per_newEmpty();
sPersona* per_new(int Id);
