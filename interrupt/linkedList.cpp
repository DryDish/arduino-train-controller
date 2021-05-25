#include "linkedList.h"
// For bool
#include <stdio.h>
// For malloc
#include <stdlib.h>


struct Node *head;
struct Node *last;
struct Node *current;

bool isEmpty()
{
    return (head == NULL);
}

void addToList(unsigned short byteOne, unsigned short byteTwo)
{
    struct Node *newNode = NULL;
    newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->byteOne = byteOne;
    newNode->byteTwo = byteTwo;

    if (isEmpty())
    {
        head = newNode;
        last = newNode;
    }
    else
    {
        last->next = newNode;
        last = newNode;
    }
    newNode->next = NULL;
}


void deleteFirstListItem()
{
    struct Node *tempNode = NULL;
    tempNode = head;

    if (head->next == NULL)
    {
        head == NULL;
        last = NULL;
    }
    head = head->next;
}

struct Node* retreiveFirstItemInList() 
{
    struct Node *tempNode = NULL;
    tempNode = head;
    if (tempNode != NULL)
    {
        tempNode = head;
        return tempNode;
    }
    return NULL;
}
