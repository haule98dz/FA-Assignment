/*******************************************************************************
* Includes
******************************************************************************/
#include "MainOperators.h"

/*******************************************************************************
* Prototypes
******************************************************************************/

/* Wait for user's respond */
inline void pause(void)
{
    printf("\nPress any key to continue...");
    getch();
}

/* These two functions below is used to draw table in console screen */
static void PrintTableHeader(void);
static void PrintTableFooter(void);

/* Swap the items of two linked list nodes */
static void swap_item(node* node1, node* node2);

/*
* @brief Search for student by account
* @return Position of student in list (=-1 if not found)
*/
static int FindByAccount(char student_account[CAPACITY_OF_FIELD_ACCOUNT]);

/*******************************************************************************
* Variables
******************************************************************************/
/* These extern variables below are from "ClassInfo.c" */
extern char data_account[NUMBER_OF_STUDENTS][CAPACITY_OF_FIELD_ACCOUNT];
extern char data_name[NUMBER_OF_STUDENTS][CAPACITY_OF_FIELD_NAME];
extern int data_mark[NUMBER_OF_STUDENTS];
extern int data_id[NUMBER_OF_STUDENTS];

/* The extern variable below is from "LinkedList.c" */
extern node* g_LinkedList_head;

/*******************************************************************************
* Code
******************************************************************************/

void List_Init(void)
{
    int i;

    for (i = NUMBER_OF_STUDENTS - 1; i >= 0; i--)
    {
        Student* student = (Student*)malloc(sizeof(Student));
        strcpy(student->account, data_account[i]);
        strcpy(student->name, data_name[i]);
        student->mark = data_mark[i];
        LinkedList_PushToHead(student);
    }
}

void PrintTutorial(void)
{
    printf("---FRESHER CLASS INFORMATION MANAGER---\n");
    printf(" Press 'f' to find a student by name.\n");
    printf(" Press 'i' to insert a student.\n");
    printf(" Press 'd' to remove a student.\n");
    printf(" Press 's' to sort the list.\n");
    printf(" Press 'a' to show all students.\n");
    printf(" Press 'e' to exit.\n");
    printf("---------------------------------------\n");
}

static void PrintStudent(Student* student, int count)
{
    printf("    | %-4d|\033[0;32m %-10s\033[0m|\033[0;32m %-20s\033[0m|\033[0;32m      %-10d\033[0m|\n", count, student->account, student->name, student->mark);
}

static void PrintTableHeader(void)
{
    printf("    __________________________________________________________\n");
    printf("    |Index|  Account  |        Name         |  Average Mark  |\n");
    printf("    |-----|-----------|---------------------|----------------|\n");
}

static void PrintTableFooter(void)
{
    printf("    |_____|___________|_____________________|________________|\n\n");
}

void Main_SearchAndPrint(void)
{
    char input_name[CAPACITY_OF_FIELD_NAME];
    printf("Type in the name to find: ");
    scanf(" %[^\n]%*c", input_name);

    node* current_node = g_LinkedList_head;
    bool flag_exist = FALSE;

    printf("Search results:\n");

    /* Search through the list and print all matching result */
    int count = 1;

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

            PrintStudent(current_node->item, count);
            count++;
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
    pause();
}

void Main_PrintAll(void)
{
    system("cls");
    node* current_node = g_LinkedList_head;
    PrintTableHeader();
    int count = 1;

    /* Search through the list and print all information */
    while (current_node != NULL)
    {
        PrintStudent(current_node->item, count);
        current_node = current_node->next;
        count++;
    }

    PrintTableFooter();
    pause();
}

void Main_Insert(void)
{
    bool flag_ValidInput = TRUE;
    int insert_position;
    int list_size = LinkedList_GetSize();

    /* Get position-to-insert, check for validity */
    do
    {
        if (flag_ValidInput == FALSE)
        {
            printf("Invalid input.\n");
        }

        printf("Please type in the position to insert (range from 1 to %d): ", list_size + 1);

        flag_ValidInput = FALSE;

        if (scanf(" %d", &insert_position) == 1)
        {
            if (insert_position >= 0 && insert_position <= list_size + 1)
            {
                flag_ValidInput = TRUE;
            }

        }
    }
    while (flag_ValidInput == FALSE);

    /* Get student's account */
    Student* student = (Student*)malloc(sizeof(Student));
    printf("    Student's account: ");
    scanf(" %[^\n]%*c", student->account);

    /* Check whether the account already exists */
    if (FindByAccount(student->account) > 0)
    {
        printf("    Student's Account must be unique. Acount %s is already appear.", student->account);
        printf("    Failed to insert.");
    }
    else
    {
        /* Get student's name */
        printf("    Student's name: ");
        scanf(" %[^\n]%*c", student->name);

        int input_mark;
        flag_ValidInput = TRUE;

        /* Get student's average mark  */
        do
        {
            if (flag_ValidInput == FALSE)
            {
                printf("    Error: Invalid input.\n");
            }

            printf("    Student's average mark (integer 0 to 100): ");
            flag_ValidInput = FALSE;

            if (scanf(" %d%*c", &input_mark) == 1)
            {
                if (input_mark >= 0 && input_mark <= 100)
                {
                    flag_ValidInput = TRUE;
                }

            }
        }
        while (flag_ValidInput == FALSE);

        student->mark = input_mark;

        /* Insert student's information to linked list */
        if (LinkedList_InsertAt(student, insert_position))
        {
            printf("Insert successfully to position %d", insert_position);
        }
        else
        {
            printf("Failed to insert.");
        }
    }

    pause();
}

void Main_Delete()
{
    int list_size = LinkedList_GetSize();

    if (list_size == 0)
    {
        printf("Linked list is empty. Nothing to delete.");
    }
    else
    {

        bool flag_ValidInput = TRUE;
        int delete_position;

        /* Get position to delete, and check for validity */
        do
        {
            if (flag_ValidInput == FALSE)
            {
                printf("Invalid input. Pleasy type again.");
            }

            printf("Please type in the position to delete (range from 1 to %d): ", list_size);

            flag_ValidInput = FALSE;

            if (scanf(" %d*%c", &delete_position) == 1)
            {
                if (delete_position >= 0 && delete_position <= list_size)
                {
                    flag_ValidInput = TRUE;
                }

            }
        }
        while (flag_ValidInput == FALSE);

        /* Print out the information of the student who is being remove */
        node* being_deleted = LinkedList_NodeAt(delete_position);
        printf("This student will be remove:\n");
        PrintTableHeader();
        PrintStudent(being_deleted->item, 1);
        PrintTableFooter();

        char input;

        /* Ask again */
        do
        {
            printf("Are you sure to continue? (y/n): ");
            scanf(" %c%*c", &input);

            if (input != 'y' && input != 'n')
            {
                input = 0;
            }
        }
        while (input == 0);

        if (input == 'y')
        {
            /* Delete node */
            if (LinkedList_DeleteAt(delete_position))
            {
                printf("Deleted successfully.");
            }
            else
            {
                printf("Failed to delete.");
            }
        }
        else
        {
            printf("Canceled.");
        }
    }

    pause();
}

void Main_Sort(void)
{
    int list_size = LinkedList_GetSize();

    if (list_size == 0)
    {
        printf("Linked list is empty, nothing to sort.\n");
    }
    else if (list_size == 1)
    {
        printf("Linked list has 1 element, sorting is needless.\n");
    }
    else
    {
        printf("    Press 'n' to sort by name.\n    Press 'm' to sort by average mark.\n    ");
        char input = 0;

        /* Get input and check for validity */
        do
        {
            scanf(" %c%*c", &input);

            if (input != 'n' && input != 'm')
            {
                input = 0;
                printf("    Invalid input, please type again.");
            }
        }
        while (input == 0);

        /* Bubble sorting */
        int i;
        int j;
        i = LinkedList_GetSize() - 1;
        node* current_node;
        node* next_node;
        Student* current_student;
        Student* next_student;

        for (; i > 0; i--)
        {
            current_node = g_LinkedList_head;

            for (j = 0; j < i; j++)
            {
                next_node = current_node->next;
                current_student = (Student*) (current_node->item);
                next_student = (Student*) (next_node->item);

                bool need_swapping;

                if (input == 'n')
                {
                    if(strcmp(current_student->name, next_student->name) > 0)
                    {
                        need_swapping = TRUE;
                    }
                    else
                    {
                        need_swapping = FALSE;
                    }
                }
                else
                {
                    if (current_student->mark < next_student->mark)
                    {
                        need_swapping = TRUE;
                    }
                    else
                    {
                        need_swapping = FALSE;
                    }
                }

                if (need_swapping == TRUE)
                {
                    swap_item(current_node, next_node);
                }

                current_node = next_node;
            }
        }

        printf("Linked list has been sorted ");

        if (input == 'n')
        {
            printf("by name.\n");
        }
        else
        {
            printf("by average mark.\n");
        }
    }

    pause();
}

static void swap_item(node* node1, node* node2)
{
    void* temp;
    temp = node1->item;
    node1->item = node2->item;
    node2->item = temp;
}

static int FindByAccount(char student_account[CAPACITY_OF_FIELD_ACCOUNT])
{
    int retVal = -1;
    node* current_node = g_LinkedList_head;
    bool flag_stop = FALSE;
    int count = 1;

    while (current_node != NULL && flag_stop == FALSE)
    {
        if (strcmp(student_account, ((Student*)(current_node->item))->account) == 0)
        {
            retVal = count;
            flag_stop = TRUE;
        }
        else
        {
            current_node = current_node->next;
            count++;
        }
    }

    return retVal;
}

