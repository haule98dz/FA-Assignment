#ifndef _MAIN_OPERATORS_H
#define _MAIN_OPERATORS_H

#include <stdio.h>
#include <stdint.h>
#include <conio.h>
#include <string.h>
#include "LinkedList.h"
#include "ClassInfo.h"

typedef struct
{
    char name[CAPACITY_OF_FIELD_NAME];
    char account[CAPACITY_OF_FIELD_ACCOUNT];
    int mark;
    int id;
} Student;

void List_Init();

void Main_Insert();
void Main_Delete();
void Main_Sort();

void Main_SearchAndPrint();
void Main_PrintAll();
void PrintStudent(Student* student, int count);

#endif/*_MAIN_OPERATORS_H*/
