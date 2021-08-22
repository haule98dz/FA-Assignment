/*******************************************************************************
* Includes
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "api.h"
#include "menu.h"

/*******************************************************************************
* Prototypes
******************************************************************************/

static void menu_input(void);
static void menu_delete(void);
static void menu_print(void);

/*******************************************************************************
* Codes API
******************************************************************************/

void menu_execute(void)
{

    printf("----ARRAY MANAGER USING LINKED LIST-----------------------\n");
    printf("  Enter 1 to set value for a specified element of the array.\n");
    printf("  Enter 2 to reset a specified element of the array.\n");
    printf("  Enter 3 to print all the values entered into the array.\n");
    printf("  Enter 4 to terminate the program.\n");
    printf("----------------------------------------------------------\n");

    bool flag_exit = false;

    while (flag_exit == false)
    {
        error_code = NO_ERROR;

        fflush(stdin); /* Clear input buffer */
        scanf(" %d", &input);

        switch (input)
        {
            case 1: /* Put value to array */
            {


                break;
            }

            case 2: /* Delete value */
            {


                break;
            }

            case 3: /* Print */
            {


                break;
            }

            case 4: /* Terminate the program. */
                flag_exit = true;
                break;
        }

        printf("\n\n");
    }

}

/*******************************************************************************
* Codes static
******************************************************************************/

static void menu_input(void)
{

    uint8_t error_code;
    int value = 0;
    int position = 0;
    
    printf("Position (0 to 19): ");
    fflush(stdin);
    scanf(" %d", &position);

    printf("Value (0 to 100): ");
    fflush(stdin);
    scanf(" %d", &value);

    error_code = api_input((uint8_t)position, (uint8_t)value);

    switch (error_code)
    {
        case NO_ERROR:
            printf("Input value successful");
            break;

        case ERROR_INPUT_INVALID_POSITION:
            printf("ERROR: Invalid position");
            break;

        case ERROR_INPUT_POSITION_HAD_VALUE:
            printf("ERROR: Position has a value already");
            break;

        case ERROR_INVALID_VALUE:
            printf("ERROR: Invalid value");
            break;

        case ERROR_INPUT_VALUE_EXISTS:
            printf("ERROR: Value exists");
            break;
    }

}

static void menu_delete(void)
{

    int value;
    uint8_t error_code;

    printf("Value (0 to 100): ");
    fflush(stdin);
    scanf(" %d", &value);

    error_code = api_delete((uint8_t)value);

    switch (error_code)
    {
        case NO_ERROR:
            printf("Deleted successfully");
            break;

        case ERROR_INVALID_VALUE:
            printf("ERROR: Invalid value");
            break;

        case ERROR_DELETE_NON_EXISTING_VALUE:
            printf("ERROR: Value do not exist in array");
            break;
    }

}

static void menu_print(void)
{

    uint8_t print_option;

    do
    {
        printf("Enter 1 to print values in unsorted order\n");
        printf("Enter 2 to print values in sorted order\n");
        fflush(stdin);
        scanf(" %d", &print_option);

        switch (print_option)
        {
            case 1:
                api_print_unsorted();
                break;

            case 2:
                api_print_sorted();
                break;

            default:
                printf("Invalid!\n Please retype: ");
                print_option = 0;
        }
    }
    while (print_option == 0);

}

