#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <stdlib.h>

int LinkedList_size;
typedef enum {FALSE, TRUE} bool;

struct t_node
{
    void *item;
    struct t_node* next;
};

typedef struct t_node node;

node* LinkedList_head;/*head*/

int LinkedList_PushToHead(void* item);/*Insert a node after head*/

int LinkedList_InsertAt(void* item, int position);/*Insert a node at specified position*/

#endif/*_LINKED_LIST_H*/
