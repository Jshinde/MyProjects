#ifndef NODE_H
#define NODE_H

/* An Implementation of the Node ADT
 *	-written by Brian P. Eddy
 */

//create a handle for nodes
typedef struct node* Node;

/* Create a new Node
 * @param value the value stored in the Node
 * @param next the node to point to from the current Node
 * @return a newly created Node
 */
Node createNode(int value, Node next);

/* Return the value of the passed in Node
 * @param Node the node to get the value from
 * @return the value for the passed in Node
*/
int getValue(Node);


/* Return the next Node pointed to by the passed in Node
 * @param Node the node to get the next Node from
 * @return the next Node from the passed in Node
*/
Node getNext(Node);


/* Set the value of the passed in Node
 * @param Node the node to set the value for
 * @param value the new value to store in the Node
*/
void setValue(Node, int value); 

/* Set the next Node of the passed in Node
 * @param Node the Node to set the next node for
 * @param next the Node to be pointed to by the given Node
*/
void setNext(Node, Node next);


/* Frees the memory allocated for the passed in Node
 * @param Node the Node to free
*/
void freeNode(Node);

#endif
