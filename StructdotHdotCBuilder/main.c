#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "steart.h"
#include "LinkedList.h"
#include "utn.h"

#define NAME_LEN 20
#define SHORT_LEN 4
#define PAR_NAME_LEN 20
#define PAR_SHORT_LEN 5
#define PAR_TYPE_LEN 15

typedef struct{
    int id;
    char parameterName[PAR_NAME_LEN];
    char parameterShort[PAR_SHORT_LEN];
    char parameterType[PAR_TYPE_LEN];
    int lenght;
}sParameter;

typedef struct{
    int id;
    char parameterName[PAR_NAME_LEN];
    char excluderType[2];
    char parameterType[PAR_TYPE_LEN];
}sExcluder;

typedef struct{
    int id;
    char parameterName[PAR_NAME_LEN];
    char parameterType[PAR_TYPE_LEN];
    int lenght;
}sChekker;

void id_asigner(int* to, int last);
int parm_idFinder(void* element, void* lookFor);
int parm_nameFinder(void* element, void* lookFor);
void show_progress(int progress);
int porcentageCalc(int base, int top);
void string_lower(char* str);
void string_upper(char* str);
void string_erase(char* s, char* b);
void myFflush(void);
void myStrcpy(char* to, const char* from);



int main()
{
    FILE* dotH;
    FILE* dotC;

    int sure;
    int more;
    char strName[NAME_LEN];
    char auxStrName[NAME_LEN] = "s\0";
    char strShort[SHORT_LEN];
    int fullPackSize = 8; //Funciones basicas de un struct newEmpty + new + show + showall
    int auxParNum = 6; //Funciones Basicas por parametro com + get + set
    int allreadyDone = 0;

    sParameter* paramA;

    LinkedList* parameterList;
    int paramLen;

    int flagFirstParam = 1;
    int flagStringHNeeded = 0;

    parameterList = ll_newLinkedList();

    do{
        progHeader("Struct DotH DotC Builder");
        subHeader("Step 1: Name your Struct");
        printf("\nThrough this program you'll be asked many times for yes or no Q's");
        printf("\nAt those times enter 1 for yes and 0 for no");
        printf("\nNothing will be saved if you close the program at a random time");
        printf("\nThe saving will only procced after the \" LAST CONFIRMATION \" Q...");
        printf("\nName in  low caps(An \"s\" will be added at the beguining): ");
        myFgets(strName,NAME_LEN);
        getInt(&sure,"Sure?(0/1): ");
    }while(!sure);
    do{
        progHeader("Struct DotH DotC Builder");
        subHeader("Step 1: Name your Struct");
        printf("\nYour Struct Named %s\nGive it a Short Name: ",strName);
        myFgets(strShort,SHORT_LEN);
        getInt(&sure,"Sure?(0/1): ");
    }while(!sure);

    do{
        paramA = (sParameter*) malloc (sizeof(sParameter));
        if(flagFirstParam)
        {
            id_asigner(&paramA->id,0);
            flagFirstParam=0;
        }
        else
        {
            id_asigner(&paramA->id,ll_len(parameterList));
        }
        paramA->lenght = 1;
        do{
            do{
                progHeader("Struct DotH DotC Builder");
                subHeader("Step 2: Name Your Parameters");
                printf("\nParameter Name: ");
                myFgets(paramA->parameterName,PAR_NAME_LEN);
                getInt(&sure,"Sure?(0/1): ");
            }while(!sure);

            do{
                progHeader("Struct DotH DotC Builder");
                subHeader("Step 2: Name Your Parameters");
                printf("\nYour Parameter Named %s\nFor Short (max 5 char): ",paramA->parameterName);
                myFgets(paramA->parameterShort,PAR_SHORT_LEN);
                getInt(&sure,"Sure?(0/1): ");
            }while(!sure);

            do{
                progHeader("Struct DotH DotC Builder");
                subHeader("Step 2: Name Your Parameters");
                printf("\nYour Parameter Named %s\nFor Short %s\nName the type (short, int, char, float, long long int, short short int): ",paramA->parameterName,paramA->parameterShort);
                myFgets(paramA->parameterType,PAR_TYPE_LEN);
                getInt(&sure,"Sure?(0/1): ");
            }while(!sure);

            if(strcmp(paramA->parameterType,"char")==0)
            {
                progHeader("Struct DotH DotC Builder");
                subHeader("Step 2: Name Your Parameters");
                getInt(&paramA->lenght,"\nThe parameter type is char, if its a string enter the lengh next else just enter 1: ");
                getInt(&sure,"Sure?(0/1): ");
                if(paramA->lenght==0)
                {
                    paramA->lenght=1;
                }
                if(paramA->lenght>1)
                {
                    flagStringHNeeded = 1;
                }
            }

            progHeader("Struct DotH DotC Builder");
            subHeader("Step 2: Name Your Parameters");
            printf("\nYour Parameter Named %s\nFor Short %s\nType %s",paramA->parameterName,paramA->parameterShort,paramA->parameterType);
            getInt(&sure,"\nAll Ok?(0/1): ");
        }while(!sure);

        ll_add(parameterList,paramA);

        progHeader("Struct DotH DotC Builder");
        subHeader("Step 2: Name Your Parameters");
        printf("\nParameter Saved");
        getInt(&more,"\nWant to add more parameters?(0/1): ");
    }while(more);


    auxParNum*= ll_len(parameterList);
    fullPackSize += auxParNum;

    show_progress(porcentageCalc(fullPackSize,allreadyDone));

    strcat(auxStrName,strName);
    strcat(auxStrName,".h");
    auxStrName[1]=toupper(auxStrName[1]);
    dotH = fopen(auxStrName,"w");
    string_erase(auxStrName,".h");
    string_upper(auxStrName);
    printf("\nfull pack size: %d\nallready: %d\n",fullPackSize,allreadyDone);
    system("pause");

    paramLen=ll_len(parameterList);

    fprintf(dotH,"\43ifndef %s_H_INCLUDED\n\43define %s_H_INCLUDED\n",auxStrName,auxStrName);
    string_lower(auxStrName);
    fprintf(dotH,"\43include \"LinkedList.h\"\n");
    auxStrName[1]=toupper(auxStrName[1]);

    fprintf(dotH,"\ntypedef struct\173\n");
    for(int i = 0; i<paramLen;i++)
    {
        paramA=(sParameter*) ll_get(parameterList,i);
        if(paramA->lenght==1)
        {
            fprintf(dotH,"    %s %s;\n",paramA->parameterType,paramA->parameterName);
        }
        else
        {
            fprintf(dotH,"    %s %s[%d];\n",paramA->parameterType,paramA->parameterName,paramA->lenght);
        }
    }
    fprintf(dotH,"\175%s;\n\n",auxStrName);

    fprintf(dotH,"\43endif // The program that made this file (and it's c partner) was made by Plain_Sight\n\n");

    allreadyDone++;
    show_progress(porcentageCalc(fullPackSize,allreadyDone));

    fprintf(dotH,"// Comparers, Getters, Setters\n\n");

    for(int i = 0; i<paramLen; i++)
    {
        paramA=(sParameter*) ll_get(parameterList,i);
        fprintf(dotH,"int %s_com%s(void* %s1, void* %s2);\n",strShort,paramA->parameterShort,strName,strName); //int %s_com%s(void* %s1; void* %s2);
        allreadyDone++;
        show_progress(porcentageCalc(fullPackSize,allreadyDone));
        fprintf(dotH,"int %s_get%s(%s* %s, %s* %s);\n",strShort,paramA->parameterShort,auxStrName,strName,paramA->parameterType,paramA->parameterName);
        allreadyDone++;
        show_progress(porcentageCalc(fullPackSize,allreadyDone));
        if(paramA->lenght==1)
        {
            fprintf(dotH,"int %s_set%s(%s* %s, %s %s);\n",strShort,paramA->parameterShort,auxStrName,strName,paramA->parameterType,paramA->parameterName);
        }
        else
        {
            fprintf(dotH,"int %s_set%s(%s* %s, %s* %s);\n",strShort,paramA->parameterShort,auxStrName,strName,paramA->parameterType,paramA->parameterName);
        }
        allreadyDone++;
        show_progress(porcentageCalc(fullPackSize,allreadyDone));
    }

    fprintf(dotH,"\n// Basic Struct Functions\n\n");

    fprintf(dotH,"void %s_show(%s* %s);\n",strShort,auxStrName,strName);//void usr_show(sUser* user)
    allreadyDone++;
    show_progress(porcentageCalc(fullPackSize,allreadyDone));


    fprintf(dotH,"int %s_showAll(LinkedList* this, char* errorMesage);\n\n",strShort);
    allreadyDone++;
    show_progress(porcentageCalc(fullPackSize,allreadyDone));


    fprintf(dotH,"\n%s* %s_newEmpty();\n",auxStrName,strShort);//auxStrName* strShort_newEmpty();
    allreadyDone++;
    show_progress(porcentageCalc(fullPackSize,allreadyDone));
    fprintf(dotH,"%s* %s_new(",auxStrName,strShort);//auxStrName* strShort_new(parametersLine);
    for(int i = 0; i<paramLen; i++)
    {
        paramA=(sParameter*) ll_get(parameterList,i);
        if(paramA->lenght==1)
        {
            fprintf(dotH,"%s %s",paramA->parameterType,paramA->parameterShort);
        }
        else
        {
            fprintf(dotH,"%s* %s",paramA->parameterType,paramA->parameterShort);
        }
        if(paramLen-1!=i)
        {
            fprintf(dotH,", ");
        }
        else
        {
            fprintf(dotH,");\n");//this should be EOF of dotH
        }
    }
    allreadyDone++;
    show_progress(porcentageCalc(fullPackSize,allreadyDone));

    fclose(dotH);

    strcat(auxStrName,".c");
    auxStrName[1]=toupper(auxStrName[1]);
    dotC = fopen(auxStrName,"w");
    string_erase(auxStrName,".c");

    fprintf(dotC,"\43include \74stdlib.h\76\n");
    fprintf(dotC,"\43include \74stdio.h\76\n");
    fprintf(dotC,"\43include \"%s.h\"\n",auxStrName);

    if(flagStringHNeeded)
    {
        fprintf(dotC,"\43include \74string.h\76\n");
    }

    fprintf(dotC,"\43include \"LinkedList.h\"\n");



    fprintf(dotC,"\n%s* %s_newEmpty()\n\173\n",auxStrName,strShort);//sUser* usr_newEmpty()
    fprintf(dotC,"    return (%s*) malloc(sizeof(%s));\n\175\n\n",auxStrName,auxStrName);//return (sUser*) malloc(sizeof(sUser));
    allreadyDone++;
    show_progress(porcentageCalc(fullPackSize,allreadyDone));

    fprintf(dotC,"%s* %s_new(",auxStrName,strShort);//auxStrName* strShort_new(parametersLine);
    for(int i = 0; i<paramLen; i++)
    {
        paramA=(sParameter*) ll_get(parameterList,i);
        if(paramA->lenght==1)
        {
            fprintf(dotC,"%s %s",paramA->parameterType,paramA->parameterName);
        }
        else
        {
            fprintf(dotC,"%s* %s",paramA->parameterType,paramA->parameterName);
        }
        if(paramLen-1!=i)
        {
            fprintf(dotC,", ");
        }
        else
        {
            fprintf(dotC,")\n\173\n");
        }
    }
    fprintf(dotC,"    %s* %s = (%s*) malloc(sizeof(%s));\n",auxStrName,strName,auxStrName,auxStrName);
    fprintf(dotC,"    if(%s!=NULL)\n\173\n",strName);
    for(int i = 0; i<paramLen; i++)
    {
        paramA=(sParameter*) ll_get(parameterList,i);
        fprintf(dotC,"        %s_set%s(%s, %s);\n",strShort,paramA->parameterShort,strName,paramA->parameterName);//usr_setId(user,id);
    }
    fprintf(dotC,"    \175\n    return %s;\n\175\n\n",strName);
    allreadyDone++;
    show_progress(porcentageCalc(fullPackSize,allreadyDone));

    for(int i = 0; i<paramLen; i++)
    {
        paramA=(sParameter*) ll_get(parameterList,i);
        if(paramA->lenght==1)
        {
            fprintf(dotC,"int %s_com%s(void* %s1, void* %s2)\n\173\n",strShort,paramA->parameterShort,strName,strName);
            fprintf(dotC,"    int anw;\n");
            fprintf(dotC,"    %s* a = (%s*) %s1;\n",auxStrName,auxStrName,strName);
            fprintf(dotC,"    %s* b = (%s*) %s2;\n",auxStrName,auxStrName,strName);
            fprintf(dotC,"    if(a->%s==b->%s)\n    \173\n",paramA->parameterName,paramA->parameterName);
            fprintf(dotC,"        anw=0;\n    \175\n");
            fprintf(dotC,"    else if(a->%s>b->%s)\n    \173\n",paramA->parameterName,paramA->parameterName);
            fprintf(dotC,"        anw=-1;\n    \175\n");
            fprintf(dotC,"    else if(a->%s<b->%s)\n    \173\n",paramA->parameterName,paramA->parameterName);
            fprintf(dotC,"        anw=1;\n    \175\n");
            fprintf(dotC,"    return anw;\n\175\n\n");

            fprintf(dotC,"int %s_get%s(%s* %s, %s* %s)\n\173\n",strShort,paramA->parameterShort,auxStrName,strName,paramA->parameterType,paramA->parameterName);
            fprintf(dotC,"    int isError = 1;\n");
            fprintf(dotC,"    if(%s!=NULL)\n    \173\n",strName);
            fprintf(dotC,"        *%s = %s->%s;\n",paramA->parameterName,strName,paramA->parameterName);
            fprintf(dotC,"        isError = 0;\n    \175\n");
            fprintf(dotC,"    return isError;\n\175\n\n");

            fprintf(dotC,"int %s_set%s(%s* %s, %s %s)\n\173\n",strShort,paramA->parameterShort,auxStrName,strName,paramA->parameterType,paramA->parameterName);
            fprintf(dotC,"    int isError = 1;\n");
            fprintf(dotC,"    if(%s!=NULL)\n    \173\n",strName);
            fprintf(dotC,"        %s->%s = %s;\n",strName,paramA->parameterName,paramA->parameterName);
            fprintf(dotC,"        isError = 0;\n    \175\n");
            fprintf(dotC,"    return isError;\n\175\n\n");
        }
        else if (strcmp(paramA->parameterType,"char")==0)
        {
            fprintf(dotC,"int %s_com%s(void* %s1, void* %s2)\n\173\n",strShort,paramA->parameterShort,strName,strName);
            fprintf(dotC,"    int anw;\n");
            fprintf(dotC,"    %s* a = (%s*) %s1;\n",auxStrName,auxStrName,strName);
            fprintf(dotC,"    %s* b = (%s*) %s2;\n",auxStrName,auxStrName,strName);
            fprintf(dotC,"    anw = strcmp(a->%s,b->%s);\n",paramA->parameterName,paramA->parameterName);
            fprintf(dotC,"    return anw;\n\175\n\n");

            fprintf(dotC,"int %s_get%s(%s* %s, %s* %s)\n\173\n",strShort,paramA->parameterShort,auxStrName,strName,paramA->parameterType,paramA->parameterName);
            fprintf(dotC,"    int isError = 1;\n");
            fprintf(dotC,"    if(%s!=NULL)\n    \173\n",strName);
            fprintf(dotC,"        strcpy(%s,%s->%s);\n",paramA->parameterName,strName,paramA->parameterName);
            fprintf(dotC,"        isError = 0;\n    \175\n");
            fprintf(dotC,"    return isError;\n\175\n\n");

            fprintf(dotC,"int %s_set%s(%s* %s, %s* %s)\n\173\n",strShort,paramA->parameterShort,auxStrName,strName,paramA->parameterType,paramA->parameterName);
            fprintf(dotC,"    int isError = 1;\n");
            fprintf(dotC,"    if(%s!=NULL)\n    \173\n",strName);
            fprintf(dotC,"        strcpy(%s->%s,%s);\n",strName,paramA->parameterName,paramA->parameterName);
            fprintf(dotC,"        isError = 0;\n    \175\n");
            fprintf(dotC,"    return isError;\n\175\n\n");
        }
        allreadyDone+=3;
        show_progress(porcentageCalc(fullPackSize,allreadyDone));
    }

    fprintf(dotC,"void %s_show(%s* %s)\n\173\n",strShort,auxStrName,strName);//void usr_show(sUser* user)
    fprintf(dotC,"    if(%s!=NULL)\n    \173\n",strName);
    fprintf(dotC,"        printf(\"");
    for(int i = 0; i<paramLen; i++)
    {
        paramA=(sParameter*) ll_get(parameterList,i);
        if(strcmp(paramA->parameterType,"char")==0)
        {
            fprintf(dotC,"%%s");
        }
        else if(strcmp(paramA->parameterType,"int")==0)
        {
            fprintf(dotC,"%%d");
        }
        else if(strcmp(paramA->parameterType,"short short int")==0)
        {
            fprintf(dotC,"%%h2d");
        }
        else if(strcmp(paramA->parameterType,"long long int")==0)
        {
            fprintf(dotC,"%%l2d");
        }
        else if(strcmp(paramA->parameterType,"float")==0)
        {
            fprintf(dotC,"%%f");
        }
        if(paramLen-1!=i)
        {
            fprintf(dotC,"|");
        }
        else
        {
            fprintf(dotC,"\134n\"");
            for(int j = 0; j<paramLen; j++)
            {
                paramA=(sParameter*) ll_get(parameterList,j);
                fprintf(dotC,",%s->%s",strName,paramA->parameterName);
            }
            fprintf(dotC,");\n");
        }
    }
    fprintf(dotC,"        printf(\"-\134n\");\n    \175\n\175\n\n");

    fprintf(dotC,"int %s_showAll(LinkedList* this, char* errorMesage)\n\173\n",strShort);
    fprintf(dotC,"    int length;\n");
    fprintf(dotC,"    int isError = 1;\n");
    fprintf(dotC,"    %s* %s;\n",auxStrName,strName);
    fprintf(dotC,"    length = ll_len(this);\n");
    fprintf(dotC,"    if(length>0)\n    \173\n");
    fprintf(dotC,"        printf(\"");
    for(int i = 0; i<paramLen; i++)
    {
        paramA=(sParameter*) ll_get(parameterList,i);
        paramA->parameterName[0]=toupper(paramA->parameterName[0]);
        fprintf(dotC,"%s",paramA->parameterName);
        paramA->parameterName[0]=tolower(paramA->parameterName[0]);
        if(paramLen-1!=i)
        {
            fprintf(dotC,"|");
        }
        else
        {
            fprintf(dotC,"\134n\");\n");
        }
    }
    fprintf(dotC,"        printf(\"-\134n\");\n");
    fprintf(dotC,"        for(int i=0; i<length; i++)\n        \173\n");
    fprintf(dotC,"            %s = (%s*) ll_get(this,i);\n",strName,auxStrName);
    fprintf(dotC,"            %s_show(%s);\n        \175\n",strShort,strName);
    fprintf(dotC,"        isError = 0;\n    \175\n");
    fprintf(dotC,"    else\n    \173\n");
    fprintf(dotC,"        printf(errorMesage);\n    \175\n");
    fprintf(dotC,"    return isError;\n\175\n");

    allreadyDone++;
    show_progress(porcentageCalc(fullPackSize,allreadyDone));

    fclose(dotC);

    ll_deleteLinkedList(parameterList);
    return 0;
}

void id_asigner(int* to, int last)
{
    *to=last+1;
}

int parm_idFinder(void* element, void* lookFor)
{
    int result = 0;
    sParameter* a;
    int id;
    a=(sParameter*) element;
    id = (int) lookFor;
    if(a->id==id)
    {
        result=1;
    }
    return result;
}

int parm_nameFinder(void* element, void* lookFor)
{
    int result = 0;
    sParameter* a;
    char* name;
    a=(sParameter*) element;
    name = (char*) lookFor;
    if(strcmp(a->parameterName,name)==0)
    {
        result=1;
    }
    return result;
}

void show_progress(int progress)
{
    progHeader("Struct DotH DotC Builder");
    subHeader("Step 3: Building Struct Filles");
    printf("\nProgress: %d%%", progress);
}

int porcentageCalc(int base, int top)
{
    int result;
    result = (100 * top)/base;
    return result;
}

void string_erase(char* s, char* b)
{
    int i = 0;
    char last = '\0';
    int lastposition;
    while(s[i])
    {
        if(last==b[0]&&s[i]==b[1])
        {
            s[lastposition]='\0';
        }
        else
        {
            lastposition = i;
            last = s[i];
        }
        i++;
    }
}

void string_upper(char* str)
{
    for(int i = 0;str[i]!='\0';i++)
    {
        if(str[i]>='a'&&str[i]<='z')
            str[i]=toupper(str[i]);
    }
}

void string_lower(char* str)
{
    for(int i = 0;str[i]!='\0';i++)
    {
        if(str[i]>='A'&&str[i]<='Z')
            str[i]=tolower(str[i]);
    }
}

void myStrcpy(char* to, const char* from)
{
    int i = 0;
    do
    {
        to[i]=from[i];
        i++;
    }while(from[i]!='\0');

}
