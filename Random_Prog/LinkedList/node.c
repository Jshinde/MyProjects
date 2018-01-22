#include <stdlib.h>
#include "node.h"

struct node {
    int value;
    Node next;
};

Node createNode(int value, Node next){
    Node newNode = malloc(sizeof *newNode);
    newNode->value = value;
    newNode->next = next;
  
    return newNode;
}

int getValue(Node current){
    return current->value;
}

Node getNext(Node current){
    return current->next;
}

void setValue(Node current, int value){
    current->value = value;
} 

void setNext(Node current, Node next){
    current->next = next;
}

void freeNode(Node current){
    free(current);
}
