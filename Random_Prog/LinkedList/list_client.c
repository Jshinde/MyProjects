#include <stdio.h>

#include "list.h"

int main()
{
    List newList = createList();
    prepend(newList,3);
    prepend(newList,2);
    prepend(newList,1);
    printf("Prepending: ");
    printList(newList);
    printf("Size: %d \n", size(newList));

    newList = createList();
    append(newList,3);
    append(newList,2);
    append(newList,1);
    printf("Appending: ");
    printList(newList);
    printf("Size: %d \n", size(newList));

    insert(newList, 2, 4);
    printf("Inserting at index 2: ");
    printList(newList);
    printf("Size: %d \n", size(newList));

    removeAt(newList, 2);
    printf("Removing at index 2: ");
    printList(newList);
    printf("Size: %d \n", size(newList));  

    removeAt(newList, 2);
    printf("Removing last element: ");
    printList(newList);
    printf("Size: %d \n", size(newList));

    insert(newList, 2, 1);
    printf("Inserting at last element: ");
    printList(newList);
    printf("Size: %d \n", size(newList));


    return 0;
}
