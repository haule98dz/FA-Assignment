#ifndef _ABSOLUTE_VALUE_
#define _ABSOLUE_VALUE_

#include <stdint.h>

/*******************************************************************************
* API
******************************************************************************/

void absoluteValue(uint8_t *data);   /*Calculate the absolute difference of two 8-bits positive integer*/
/*Input:
      Address of an array of 3 byte
          byte 0: Value of the first number
          byte 1: Value of the second number
          byte 2: To store the output
  Output:
      The result is stored in data[2]
*/

#endif

