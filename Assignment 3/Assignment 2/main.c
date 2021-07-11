#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "absoluteValue.h"

/*******************************************************************************
* Code
******************************************************************************/

int main() {
    bool stop = false;
    char command;
    uint8_t *data;
    data = (uint8_t*) malloc(3);        /*allocate 3 bytes to store inputs and output*/
    do {
       printf("a = ");
       scanf("%hhu", &data[0]);         /*scan input of type 8-bits unsigned interger*/
       printf("b = ");
       scanf("%hhu", &data[1]);         /*scan input of type 8-bits unsigned interger*/

       getchar();                       /*scan the New Line character*/

       absoluteValue(data);
       printf("|a-b| = %hhu", data[2]); /*process and print result*/

/* Ask user whether they want to continue.*/
       bool invalid_command;
       do {
           invalid_command = false;
           printf("\nDo you want to calculate more? (y/n) ");
           command = getchar();
           switch (command) {
               case 'y': case 'Y':
                   break;
               case 'n': case 'N':
                   stop = true;
                   break;
               default:
                   invalid_command = true;
           }
           getchar();                   /*scan the New Line character*/
       } while (invalid_command);

    } while (!stop);

    return 0;
}

