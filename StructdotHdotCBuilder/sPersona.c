#include <stdlib.h>
#include <stdio.h>
#include "sPersona.h"
#include "LinkedList.h"

sPersona* per_newEmpty()
{
    return (sPersona*) malloc(sizeof(sPersona));
}

sPersona* per_new(int id)
{
    sPersona* persona = (sPersona*) malloc(sizeof(sPersona));
    if(persona!=NULL)
{
        per_setId(persona, id);
    }
    return persona;
}

int per_comId(void* persona1, void* persona2)
{
    int anw;
    sPersona* a = (sPersona*) persona1;
    sPersona* b = (sPersona*) persona2;
    if(a->id==b->id)
    {
        anw=0;
    }
    else if(a->id>b->id)
    {
        anw=-1;
    }
    else if(a->id<b->id)
    {
        anw=1;
    }
    return anw;
}

int per_getId(sPersona* persona, int* id)
{
    int isError = 1;
    if(persona!=NULL)
    {
        *id = persona->id;
        isError = 0;
    }
    return isError;
}

int per_setId(sPersona* persona, int id)
{
    int isError = 1;
    if(persona!=NULL)
    {
        persona->id = id;
        isError = 0;
    }
    return isError;
}

void per_show(sPersona* persona)
{
    if(persona!=NULL)
    {
        printf("%d\n",persona->id);
        printf("-\n");
    }
}

int per_showAll(LinkedList* this, char* errorMesage)
{
    int length;
    int isError = 1;
    sPersona* persona;
    length = ll_len(this);
    if(length>0)
    {
        printf("Id\n");
        printf("-\n");
        for(int i=0; i<length; i++)
        {
            persona = (sPersona*) ll_get(this,i);
            per_show(persona);
        }
        isError = 0;
    }
    else
    {
        printf(errorMesage);
    }
    return isError;
}
