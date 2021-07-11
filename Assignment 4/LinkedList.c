#include "LinkedList.h"

static void LinkedList_InsertAfter(node* node_before, void* item);/*Insert a node after a specified node*/

int LinkedList_PushToHead(void* item)
{
    node* new = (node*)malloc(sizeof(node));/*Allocate memory for the new node*/
    new->item = item;
    new->next = LinkedList_head;/*Set the <'next pointer' of the new node> to point at <address of the node which the LinkedList_head is pointing at>*/
    LinkedList_head = new;/*set the <LinkedList_head pointer> to point at <address of the new node>*/
    return TRUE;
}

void LinkedList_InsertAfter(node* node_before, void* item) {
    node* new_node = (node*)malloc(sizeof(node));/*Allocate memory for the new node*/
    new_node->item = item;

    new_node->next = node_before->next;/*Set the <'next pointer' of the new node> to point at <address of the node which the node_before is pointing at>*/
    node_before->next = new_node;/*Set the <'next pointer' of the node_before> to point at <address of the new node>*/
}

int LinkedList_InsertAt(void* item, int position)
{
    bool flag_success = FALSE;

    if (position == 0)
    {
        flag_success = LinkedList_PushToHead(item);
    }
    else
    {
        int count = 1;
        node* current_node;
        current_node = LinkedList_head;/*start from first node (the node that LinkedList_head pointer is pointing at*/

        while (current_node != NULL || flag_success)
        {
            if (count == position)
            {
                LinkedList_InsertAfter(current_node, item);
                flag_success = TRUE;
            }
            else
            {
                count++;
                current_node = current_node->next;/*Go to the next node*/
            }
        }
    }

    return flag_success;
}

