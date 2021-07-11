#include "Assignment1.h"

/*******************************************************************************
* Code
******************************************************************************/

bool allocate10Bytes(uint8_t **outPtr) {         //Address of the pointer is passed as an argument
    *outPtr = NULL;
    *outPtr = (uint8_t*) malloc(10*sizeof(int)); //Allocate memory and save the new pointer at that adress
    return (*outPtr != NULL);                    //Return 0 if pointer is still NULL, else return 1
}

