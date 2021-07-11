#include "MainOperators.h"

int main(void)
{
    List_Init();

    while (1)
    {
        system("cls");
        PrintTutorial();

        char input;
        scanf(" %c%*c", &input);

        switch (input)
        {

            case 'i':
                Main_Insert();
                break;

            case 'd':
                Main_Delete();
                break;

            case 'f':
                Main_SearchAndPrint();
                break;

            case 'a':
                Main_PrintAll();
                break;

            case 's':
                Main_Sort();
                break;

            case 'e':
                exit(0);
        }
    }

    return 0;
}


