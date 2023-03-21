#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include "AdptArray.h"

struct AdptArray_
{
    int arrSize;
    PElement* pElement;
    COPY_FUNC copyFunc;
    DEL_FUNC delFunc;
    PRINT_FUNC printFunc;

}AdptArray;



PAdptArray CreateAdptArray(COPY_FUNC copyFunc , DEL_FUNC delElementFunc,PRINT_FUNC printFunc){
     
    PAdptArray pDB;//new struct pointer
    pDB = (PAdptArray)malloc(sizeof(AdptArray));//allocate memory
    if(pDB == NULL)
        return NULL;

    pDB->arrSize=0;
    pDB->pElement = NULL;

    //pointers to element function 
    pDB->copyFunc = copyFunc;
    pDB->delFunc = delElementFunc;
    pDB->printFunc = printFunc;

    return pDB;
}



void DeleteAdptArray(PAdptArray pDB){
    if(pDB == NULL)
        return;
    //free all elements memory by their func pointers
    for(int i=0 ; i < pDB->arrSize ; i++){
        if((pDB->pElement)[i] != NULL)
            pDB->delFunc((pDB->pElement)[i]);
    }
    //free struct & element memory
    free(pDB->pElement);
    free(pDB);

}

Result SetAdptArrayAt(PAdptArray pDB, int index, PElement setElement){
    PElement* newElement;

    if(pDB == NULL)
        return FAIL;

    //if index > size extend the array 
    if(index >= pDB->arrSize){
        if((newElement = (PElement*)calloc((index+1) , sizeof(PElement)))==NULL)
            return FAIL;        
        memcpy(newElement , pDB->pElement , (pDB->arrSize)*sizeof(PElement));
        free(pDB->pElement);
        pDB->pElement = newElement;
    }

    (pDB->pElement)[index] = pDB->copyFunc(setElement);

    pDB->arrSize = (index >= pDB->arrSize) ? (index + 1) : pDB->arrSize;

    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pDB, int index){
    if(pDB == NULL || index>= pDB->arrSize || (pDB->pElement)[index] == NULL)
        return NULL;
    PElement* returnElement = pDB->copyFunc((pDB->pElement)[index]);

    return returnElement;
}

int GetAdptArraySize(PAdptArray pDB){
    if(pDB == NULL)
        return -1;

    return pDB->arrSize;
}

void PrintDB(PAdptArray pDB){
    if(pDB == NULL)
        return;
    for(int i=0 ; i < pDB->arrSize ; i++){
        if((pDB->pElement)[i] != NULL){
            pDB->printFunc((pDB->pElement)[i]);         
        }
    }

}