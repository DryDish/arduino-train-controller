#include "linkedList.h"

struct Node {
    unsigned short byteOne;
    unsigned short byteTwo;
    bool *bitIsOne;
    bool *hasBit;
    struct Node *next;
};

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

void printList() {

    //start from the beginning
    Node *tempNode = NULL;
    tempNode = head;

    //navigate till the end of the list
    Serial.print("\n[ ");

    while(tempNode != NULL) {
        Serial.print("(%d,%d,%d,%d) ",tempNode->byteOne,tempNode->byteTwo,tempNode->hasBit,tempNode->bitIsOne);
        tempNode = tempNode->next;
    }

    Serial.println(" ]");
}
