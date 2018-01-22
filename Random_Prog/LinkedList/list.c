#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "node.h" //list is built upon nodes

struct list {
    int size;
    Node head;
    Node tail;
};

List createList(){
    List newList = malloc(sizeof *newList);
    //no nodes yet, so set both head and tail to NULL
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;    

    return newList;
}

int size(List currentList)
{
    return currentList->size;
}

void prepend(List currentList, int value){
    //create the new node that we are adding
    //the new node will point to the old head
    Node newNode = createNode(value, currentList->head);
    //update the head to be the new node
    currentList->head = newNode;

    //if this is the first node we have added, then we also need
    //to update the tail to be the new node
    if(currentList->tail == NULL)
        currentList->tail = currentList->head;

    ++currentList->size; //increment the size of the list
}

void append(List currentList, int value){
    //create the new node that we are going to add
    Node newNode = createNode(value, NULL);
    ++currentList->size; //we will be increasing the size of the list

    //if no nodes have been added, then both the head and tail 
    //will need to point to this new node
    if(currentList->tail == NULL){
        currentList->head = newNode;
        currentList->tail = newNode;
        return;
    }

    //otherwise, the old tail will need to point to this new node
    setNext(currentList->tail, newNode);
    //update the tail so the new node is our new tail
    currentList->tail = newNode;
}

void insert(List currentList, int index, int value){

    //prepend and append will properly update head and tail,
    //use them if possible
    if(index == 0) //if inserting at beginning, use prepend
    {
        prepend(currentList, value);
        return;
    }
   
    if(index == currentList->size) //if inserting at end, use append
    {
        append(currentList, value);
        return;
    }

    if(index > currentList->size) //make sure index is in range
    {
        printf("Index is out of range for insert.\n");
        exit(1);
    }

    //we can't directly index into a linked list, so we have to loop
    //we will need to go until we are before where we want to insert
    //this will enable us to update the next pointer for the node
    //that will proceed our inserted node
    //start looping at the head
    Node currentNode = currentList->head;
    //loop until we are before where we want to insert
    int i;
    for(i = 0; i < index-1; ++i)
        currentNode = getNext(currentNode); //move to next node
    //create a new node and point it to the current node's next
    Node newNode = createNode(value, getNext(currentNode));
    //update the current node to point to the new node
    setNext(currentNode, newNode);
    ++currentList->size; //increase size of the list
}

int removeAt(List currentList, int index){
    //don't remove anything from an empty list
    //or if index is out of bounds
    if(currentList->size == 0 || index >= currentList->size)
    {
        printf("Cannot remove element from the list. \n");
        exit(1);
    }


    //start at the beginning of the linked list
    Node currentNode = currentList->head;
    //we treat index 0 differently because we don't need to update
    //a next pointer
    --currentList->size; //go ahead and decrease size of list
    if(index == 0)
    {
        currentList->head = getNext(currentNode);
        int value = getValue(currentNode); //save our result value
        freeNode(currentNode); //FREE MEMORY
        if(currentList->size == 0) //if we removed the only element
            currentList->tail = NULL; //we need to update the tail
        return value;
    }
    
    //loop until we are before where we want to remove
    int i;
    for(i = 0; i < index-1; ++i)
        currentNode = getNext(currentNode); //move to next node
    //we will need to temporarily store the node we are removing
    Node removeNode = getNext(currentNode);
    //next we point the current node to the next of the node we are removing
    setNext(currentNode, getNext(removeNode));
    //we will need to update the tail if we removed the last element
    if(index == currentList->size)
        currentList->tail = currentNode;

    //now that nothing is pointing to the node we are removing,
    //save the value from the removed node and free the memory for the node
    int value = getValue(removeNode);
    freeNode(removeNode);//FREE MEMORY
    return value;
}

int get(List currentList, int index){
    if(currentList->size == 0 || index >= currentList->size)
    {
        printf("Cannot get a value from given index. \n");
        exit(1);
    }

    //start looping at the beginning
    Node currentNode = currentList->head;
    int i;
    //we are actually going to the position passed in this time
    for(i = 0; i < index; ++i)
        currentNode = getNext(currentNode); //move to next node
    return getValue(currentNode); //return the value of the current node
}

void printList(List currentList){
    //we will display a linked list as [v1 v2 v3 v4]
    //where each v# is an integer in the linked list
    printf("[");//print the opening [
    Node currentNode = currentList->head;
    
    //let's use a while loop this time
    //we will know when we have reached the end of the list
    //when the currentNode is NULL
    while(currentNode != NULL)
    {
        printf("%d",getValue(currentNode));
        if(getNext(currentNode) != NULL)
            printf(" ");
        currentNode = getNext(currentNode);
    }
    printf("] \n"); //wrap things up
}

void freeList(List currentList){
    //freeing may seem a little tricky, we will need
    //to pass over the list and free each item
    //before we can free the list
    Node currentNode = currentList->head; //start at head
    while(currentNode != NULL)
    {
        Node next = getNext(currentNode);//temporarily hold next
        freeNode(currentNode);//free current
        currentNode = next;//set current to the next node
    }
    free(currentList);//finally, free the linked list
}

