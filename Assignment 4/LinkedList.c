#include "LinkedList.h"

static int LinkedList_InsertAfter(node* node_before, void* item);/*Insert a node after a specified node*/

int LinkedList_GetSize() {
    int retVal = 0;
    node* current_node = g_LinkedList_head;
    while (current_node != NULL) {
        current_node = current_node->next;
        retVal ++;
    }
    return retVal;
}

int LinkedList_PushToHead(void* item)
{
    node* new = (node*)malloc(sizeof(node));/*Allocate memory for the new node*/
    new->item = item;
    new->next = g_LinkedList_head;/*Set the <'next pointer' of the new node> to point at <address of the node which the g_LinkedList_head is pointing at>*/
    g_LinkedList_head = new;/*set the <g_LinkedList_head pointer> to point at <address of the new node>*/
    return TRUE;
}

int LinkedList_InsertAfter(node* node_before, void* item) {
    node* new_node = (node*)malloc(sizeof(node));/*Allocate memory for the new node*/
    new_node->item = item;

    new_node->next = node_before->next;/*Set the <'next pointer' of the new node> to point at <address of the node which the node_before is pointing at>*/
    node_before->next = new_node;/*Set the <'next pointer' of the node_before> to point at <address of the new node>*/

    return TRUE;
}

int LinkedList_InsertAt(void* item, int position)
{
    bool flag_success = FALSE;

    if (position == 1)
    {
        flag_success = LinkedList_PushToHead(item);
    }
    else
    {
        int count = 2;
        node* current_node;
        current_node = g_LinkedList_head;/*start from first node (the node that g_LinkedList_head pointer is pointing at*/

        while (current_node != NULL && flag_success == FALSE)
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

int LinkedList_DeleteAt(int delete_position) {
    bool flag_success = FALSE;
    node* current_node;
    node* previous_node;

    current_node = g_LinkedList_head;

    if (delete_position == 1) {
        g_LinkedList_head = current_node->next;
        free(current_node);
        flag_success = TRUE;
    } else {
        int count = 2;
        while (current_node->next != NULL && flag_success == FALSE) {
            previous_node = current_node;
        current_node = previous_node->next;

            if (count == delete_position) {
                previous_node->next = current_node->next;
                free(current_node);

                flag_success = TRUE;
            } else {
                count++;
            }
        }
    }
    return flag_success;
}

node* LinkedList_NodeAt(int position) {
    int count = 1;
    node* current_node = g_LinkedList_head;

    bool flag_stop = FALSE;
    while (current_node != NULL && flag_stop == FALSE) {
        if (count != position) {
            count++;
            current_node = current_node->next;
        } else {
            flag_stop = TRUE;
        }
    }

    return current_node;
}

