#include <stdio.h>

#include "node.h"

int main()
{
    Node secondNode = createNode(0,NULL);//create the second node in the list
    //create the first node in the list
    //will point to the second node
    Node firstNode = createNode(1, secondNode);
    
    setValue(secondNode,2);//change the value of the secondNode
    //print the value of each node individually
    printf("First Node's value: %d \n",getValue(firstNode));
    printf("Second Node's value: %d \n",getValue(secondNode));

    //print the value of the second node by traversing through the first
    //notice that we are nesting function calls
    printf("Second Node's value by traversal: %d \n",getValue(getNext(firstNode)));
    
    //print the value of the second node after freeing memory
    freeNode(secondNode);
    printf("Second Node's value after free: %d \n", getValue(secondNode));
    return 0;
}
