#include <stdio.h>
#include <stdint.h>
#include <conio.h>
#include <string.h>
#include "ClassInfo.h"
#include "LinkedList.h"

typedef struct
{
    char* name;
    char* account;
    int mark;
    int id;
} Student;

static void PrintTutorial();
static void PrintStudent(Student* student);
static void PrintTableHeader();
static void PrintTableFooter();
static void List_Init();
static void Main_SearchAndPrint();
static void Main_Insert();
static void Main_PrintAll();
inline void pause();

int main(void)
{
    int i;

    for (i = NUMBER_OF_STUDENTS - 1; i >= 0; i--)
    {
        Student* student = (Student*)malloc(sizeof(Student));
        student->id = id_array[i];
        student->account = account_array[i];
        student->name = name_array[i];
        student->mark = mark_array[i];

        LinkedList_PushToHead(student);
    }

    /**/
    char command;
    node* current_node;

    while (1)
    {
        system("cls");
        PrintTutorial();
        scanf("%c%*c", &command);

        switch (command)
        {
            case 'i':
                Main_Insert();
                pause();
                break;

            case 'f':
            {
                Main_SearchAndPrint();
                pause();
                break;
            }

            case 'a':
                Main_PrintAll();
                pause();
                break;

        }
    }

    return 0;
}

void PrintTutorial()
{
    printf("---FRESHER CLASS INFORMATION MANAGER---\n");
    printf(" Press 'f' to find a student by name.\n");
    printf(" Press 'i' to insert a student.\n");
    printf(" Press 'd' to remove a student.\n");
    printf(" Press 's' to sort the list.\n");
    printf(" Press 'a' to show all students.\n");
    printf(" Press 'e' to exit.\n");
}

void PrintStudent(Student* student)
{
    printf("    | %-10d| %-10s| %-20s|      %-10d|", student->id, student->account, student->name, student->mark);
}

void PrintTableHeader()
{
    printf("    ________________________________________________________________\n");
    printf("    |Student ID |  Account  |        Name         |  Average Mark  |\n");
    printf("    |-----------|-----------|---------------------|----------------|\n");
}

void PrintTableFooter()
{
    printf("    |___________|___________|_____________________|________________|\n");
}

void List_Init()
{
    LinkedList_head = NULL;
    int i;

    for (i = NUMBER_OF_STUDENTS - 1; i >= 0; i--)
    {
        Student* student = (Student*)malloc(sizeof(Student));
        student->id = id_array[i];
        student->account = account_array[i];
        student->name = name_array[i];
        student->mark = mark_array[i];

        LinkedList_PushToHead(student);
    }
}

void Main_SearchAndPrint()
{
    char input_name[CAPACITY_OF_FIELD_NAME];
    printf("Type in the name to find: ");
    scanf("%[^\n]%*c", input_name);

    node* current_node = LinkedList_head;
    bool flag_exist = FALSE;

    /*search through the list and print all matching result*/
    printf("Search results:\n");

    while (current_node != NULL)
    {
        char *current_node__name = ((Student*)(current_node->item))->name;

        if (strcmp(current_node__name, input_name) == 0)
        {
            if (flag_exist == FALSE)
            {
                PrintTableHeader();
                flag_exist = TRUE;
            }

            PrintStudent(current_node->item);
            putchar('\n');
        }

        current_node = current_node->next;
    }

    if (flag_exist)
    {
        PrintTableFooter();
    }
    else
    {
        printf(" No matching.\n");
    }

    printf("Searching completed.");
}

void Main_PrintAll()
{
    system("cls");
    node* current_node = LinkedList_head;
    PrintTableHeader();

    while (current_node != NULL)
    {
        PrintStudent(current_node->item);
        putchar('\n');
        current_node = current_node->next;
    }

    PrintTableFooter();
}

void Main_Insert()
{
}
inline void pause()
{
    printf("\nPress any key to continue...");
    getch();
}
