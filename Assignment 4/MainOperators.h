#ifndef _MAIN_OPERATORS_
#define _MAIN_OPERATORS_

/*******************************************************************************
* Includes
******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <conio.h>
#include <string.h>
#include "LinkedList.h"
#include "ClassInfo.h"

/*******************************************************************************
* Definition
******************************************************************************/
typedef struct
{
    char name[CAPACITY_OF_FIELD_NAME];
    char account[CAPACITY_OF_FIELD_ACCOUNT];
    int mark;
} Student;

/*******************************************************************************
* API
******************************************************************************/
void List_Init(void); /*Initiate data in linked list*/

void Main_Insert(void); /*Users type in position to insert and data to insert. Insert data into linked list.*/

void Main_Delete(void); /*Users type in position to delete. Delete data from linked list.*/

void Main_Sort(void); /*Sort the list by name or by average mark.*/

void Main_SearchAndPrint(void); /*Users type in student's name. Search in linked list and print the information of all matching case.*/

void Main_PrintAll(void); /*Print informations of all students.*/

void PrintTutorial(void);

#endif /*_MAIN_OPERATORS_*/

