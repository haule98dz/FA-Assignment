/*******************************************************************************
* Includes
******************************************************************************/
#include "MainOperators.h"

/*******************************************************************************
* Code
******************************************************************************/
int main(void)
{
    List_Init(); /* Initiate data in linked list */

    while (1)
    {
        system("cls"); /* Clear screen */
        PrintTutorial();

        /* Get input from keyboard */
        char input;
        scanf(" %c", &input);
        fflush(stdin);
        
        switch (input)
        {
            case 'i': /* Insert a student.*/
                Main_Insert();
                break;

            case 'd': /* Remove a student.*/
                Main_Delete();
                break;

            case 'f': /* Search students by name, show information of all matched students.*/
                Main_SearchAndPrint();
                break;

            case 'a': /* Print full list of student in fresher class.*/
                Main_PrintAll();
                break;

            case 's': /* Sort linked list.*/
                Main_Sort();
                break;

            case 'e': /* Exit.*/
                exit(0);
        }
        /* Flush input stream */
        fflush(stdin);
    }

    return 0;
}

