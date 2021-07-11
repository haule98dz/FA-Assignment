#ifndef _ASSIGNMENT1_
#define _ASSIGNMENT1_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

/*******************************************************************************
* API
******************************************************************************/

bool allocate10Bytes(uint8_t **outPtr); //Allocate 10 bytes of 8-bits unsigned int
/*Input
      The address of the output pointer
  Output:
      Allocated pointer
      Return: TRUE if allocate successfully, otherwise return FALSE
*/

#endif /*_ASSIGNMENT1_*/

