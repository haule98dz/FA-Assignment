/*******************************************************************************
* Includes
******************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "api.h"

/*******************************************************************************
* Prototypes
******************************************************************************/

/*
* @brief Search for a value in array
* @param value Value to search
* @return Index of value in array ( = 0xFF if not found)
*/
static uint8_t api_search(uint8_t value);

/*
* @brief Insert a value to linklist and to array,
         maintain the increasing order in linklist
* @param index_in_array Index to insert in array
* @param value Value to be inserted
* @return Void
*/
static void api_linkedlist_insert_order(uint8_t index_in_array, uint8_t value);

/*******************************************************************************
* Variables
******************************************************************************/

uint8_t assignment4[20] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

uint8_t next_index[20] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

uint8_t head = 0xFF;

/*******************************************************************************
* Codes API
******************************************************************************/

uint8_t api_input(uint8_t index, uint8_t value)
{

    uint8_t error_code = NO_ERROR;

    if (index > 19) /* uint8_t index always > 0 */
    {
        error_code = ERROR_INPUT_INVALID_POSITION;
    }
    else if (assignment4[index] != 0xFF)
    {
        error_code = ERROR_INPUT_POSITION_HAD_VALUE;
    }
    else if (value < 0 || value > 100)
    {
        error_code == ERROR_INVALID_VALUE;
    }
    else if (api_search(value) != 0xFF)
    {
        error_code = ERROR_INPUT_VALUE_EXISTS;
    }
    else
    {
        api_linkedlist_insert_order(index, value);
    }

    return error_code;
}

uint8_t api_delete(uint8_t value)
{

    uint8_t error_code = NO_ERROR;
    uint8_t *current;
    int i = 0;

    if (value < 0 || value > 100)
    {
        error_code = ERROR_INVALID_VALUE;
    }
    else if (api_search(value) == 0xFF)
    {
        error_code = ERROR_DELETE_NON_EXISTING_VALUE;
    }
    else
    {
        current = &head;

        while (*current != 0xFF)
        {
            if (assignment4[*current] == value)
            {
                assignment4[*current] = 0xFF;
                *current = next_index[*current];
                break;
            }
            else
            {
                current = &next_index[*current];
            }
        }
    }

    return error_code;
}

void api_print_unsorted(void)
{

    int index;

    printf("Values of array in unsorted order: ");
    for (index = 0; index < 20; index++)
    {
        if (assignment4[index] != 0xFF)
        {
            printf("%d  ", assignment4[index]);
        }
    }

}

void api_print_sorted(void)
{

    uint8_t current_index = head;

    printf("Values of array in sorted order: ");

    while (current_index != 0xFF)
    {
        printf("%d  ", assignment4[current_index]);
        current_index = next_index[current_index];
    }
}

/*******************************************************************************
* Codes static
******************************************************************************/

/* Insert but maintain order */
static void api_linkedlist_insert_order(uint8_t index_in_array, uint8_t value)
{
    uint8_t *current = &head;

    while (*current != 0xFF)
    {
        if (assignment4[*current] > value)
        {
            break;
        }

        current = &(next_index[*current]);
    }

    next_index[index_in_array] = *current;
    *current = (uint8_t)index_in_array;
    assignment4[index_in_array] = value;

}

/* Search for a value using linked list */
static uint8_t api_search(uint8_t value)
{

    uint8_t retVal = 0xFF;
    uint8_t index;

    for (index = 0; index < 20; index++)
    {
        if (assignment4[index] == value)
        {
            retVal = index;
            break;
        }
    }

    return retVal;
}

