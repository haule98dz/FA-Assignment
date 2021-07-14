#ifndef _LINKED_LIST_
#define _LINKED_LIST_

/*******************************************************************************
* Includes
******************************************************************************/
#include <stdint.h>
#include <stdlib.h>

/*******************************************************************************
* Definitions
******************************************************************************/
typedef enum
{
    FALSE,
    TRUE
} bool;

/* Linked list node */
typedef struct node
{
    uint8_t* address_of_data;
    struct node* next;
} Node;

/*******************************************************************************
* API
******************************************************************************/
extern Node* LinkedList_head;

/*@brief Insert a node after a specified node */
void LinkedList_InserAfter(Node* previous_node, Node* new_node);

/*
* @brief Insert a node atr a specified node
* @return TRUE if success, FALSE if failed
*/
bool LinkedList_DeleteAt(int position);

/*
* @brief Search by data
* @return Position of matched data in the list ( = -1 if not found)
*/
int LinkedList_Search(uint8_t searching_data);

#endif /* _LINKED_LIST_ */

