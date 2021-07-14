#ifndef _LINKED_LIST_
#define _LINKED_LIST_

/*******************************************************************************
* Includes
******************************************************************************/
#include <stdlib.h>

/*******************************************************************************
* Definitions
******************************************************************************/
typedef enum {FALSE, TRUE} bool;

struct t_node
{
    void *item;
    struct t_node* next;
};

typedef struct t_node node;

/*******************************************************************************
* API
******************************************************************************/
int LinkedList_GetSize(void);

int LinkedList_PushToHead(void* item);/*Insert a node after head.*/

int LinkedList_InsertAt(void* item, int position);/*Insert a node at specified position.*/

int LinkedList_DeleteAt(int position);/*Delete a node at specified position.*/

node* LinkedList_NodeAt(int position);/*Get address of the node at specified position.*/

#endif /*_LINKED_LIST_*/

