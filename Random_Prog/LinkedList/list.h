#ifndef LIST_H
#define LIST_H

/* Wraps around Node to add important functions for a singly-linked list
 * 	- written by Brian P. Eddy
*/

//create a handle for lists
typedef struct list* List;

/* Creates a new non-circular singly-linked list
 * @return returns a new empty list
*/
List createList();

/* Get the size of the linked list
 * @param List the list we need the size of
 * @return the size of the linked list
*/
int size(List);


/* Adds an element to the beginning of a linked list
 * @param List the list to add elements to
 * @param value the item to add to the beginning of the list
*/ 
void prepend(List,int value);

/* Adds an element to the end of a linked list
 * @param List the list to add elements to
 * @param value the item to add to the end of the list
*/
void append(List,int value);

/* Inserts an element into a position in the linked list
 * @param List the list to insert elements into
 * @param index where to insert the element
 * @param value the item to insert into the list
*/
void insert(List, int index, int value);

/* Removes an element from a position in the linked list
 * @param List the list to remove elements from
 * @param index where to remove the element from
 * @return the value of the element that was removed
*/
int removeAt(List, int index);

/* Gets an element from a position in the linked list without removing
 * @param List the list to get the element from
 * @param index where to get the element from
 * @return the value of the element that was retrieved
*/
int get(List, int index);

/* Prints the elements in the list
 * @param List the list to print out
*/
void printList(List);

/* Frees the memory allocated for the list
 * @param List the list to free
*/
void freeList(List);

#endif
