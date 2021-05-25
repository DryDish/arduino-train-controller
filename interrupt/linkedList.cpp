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

void addToListEnd(unsigned short byteOne, unsigned short byteTwo, bool *bitIsOne, bool *hasBit)
{
    Node *newNode = NULL;
    newNode = (Node *)malloc(sizeof(struct Node));
    newNode->byteOne = byteOne;
    newNode->byteTwo = byteTwo;
    newNode->bitIsOne = bitIsOne;
    newNode->hasBit = hasBit;

    if (isEmpty())
    {
        head = newNode;
        last = newNode;
    } else {
        last->next = newNode;
        last = newNode;
    }
}


void deleteFirstListElement()
{
    Node *tempNode = NULL;
    tempNode = head;

    if (head->next == NULL)
    {
        last = NULL;
    }
    head = head->next;
}

Node* retreiveFirstItemInList() {
    //start from the beginning
    Node *tempNode = NULL;
    if (head != NULL)
    {
        tempNode = head;
    }
    return tempNode;
}
