/**
 * File full of helper functions for tspGenetic and tspBruteForce
 * 
 * @author Daniel Belcher 
 * @author Joshua Shinde
 * @date 4/12/2017
 * @info Course COP3014
 */
#include <stdio.h>
#include <stdlib.h>
#include "helper.h"

/**
 * Creates and allocates room for the graph
 *
 * @param numCity number of cities we use in the graph
 *
 * @return the graph we have created and allocated.
 */
GraphT* initGraph(int numCity)
{
   GraphT* temp = malloc(sizeof(GraphT));
   temp->list = (char*)malloc(sizeof(char) * numCity);
   temp->values = (int**)malloc(sizeof(int*) * numCity);

   int i, j;
   for(i = 0; i < numCity; i++){
      temp->values[i] = (int*)malloc(sizeof(int) * numCity);

      // initialize all weights to -1 to indicate that there is no connection
      for (j=0; j < numCity; j++)
         (temp->values[i])[j] = -1;
   }


  
   // at the beginning there is no city recorded yet
   temp->length = 0;

   return(temp);
   
}

/**
 * Adds cities and the cost of their paths to the graph 
 *
 * @param city1 city letter 1
 * @param city2 city letter 2
 * @param cost cost of path between city 1 & 2
 * @param graph graph we are inserting into 
 *
 * @return the error code, 0 represents success and -1 represents failure
 */
void insert (char city1, char city2, int cost, GraphT* graph)
{
    int i, j;
    for (i=0; i < graph->length; i++)
      if (city1 == graph->list[i]) break;
    if (i == graph->length) {
        graph->list[i] = city1;
        graph->length++;
    }
    // more stuff 
    for (j=0; j < graph->length; j++)
      if (city1 == graph->list[j]) break;
    if (j == graph->length) 
	{
        graph->list[j] = city1;
        graph->length++;
    }
    (graph->values[i])[j] = cost;
    (graph->values[j])[i] = cost;
}

/**
 * Creates and initializes a graph, then opens our graph file and fill said graph, returning it.
 *
 * @param numCity how many cities are in the graph
 * @param filename name of file we have to open
 *
 * @return graph struct to the main.
 */
GraphT* readFile(int numCity, char* filename)
{
   char city1, city2;
   int cost;
   
   FILE *file = fopen(filename, "r");
   
   if(file == NULL)
   {
      return NULL;
   }

   GraphT* temp = initGraph(numCity);

   while(!feof(file))
   {
      fscanf (file, "%c,%c,%d", &city1, &city2, &cost);
      if(feof(file))
	break;
      insert (city1, city2, cost, temp);
   }
   return (temp);
}

/**
 * Returns the cost of the path passed
 *
 * @param tempList path we are checking cost of
 * @param x the graph we are pulling the weight of the list from
 *
 * @return the weight of the path through the graph
 */
int checkCost(int* tempList, GraphT* x)
{
   int i, sum;
   i = sum = 0;
   
   while(i < (x->length)){
      sum += (x->values[tempList[i]][tempList[i + 1]]);
      i++;
   }
   
   return(sum);
   
}

/**
 * swaps two locations in a path
 *
 * @param tempList list we are swapping in
 * @param x y the two locations that are being swapped
 *
 * @return the error code, 0 represents success and -1 represents failure
 */
void swapSpots(int* tempList, int x, int y)
{
   int temporary = 0;
   temporary = tempList[x];
   tempList[x] = tempList[y];
   tempList[y] = temporary;
}

/**
 * returns a new path that is a copy of the old one
 *
 * @param temp the list we are copying
 * @param newList the list we are copying to
 *
 * @return the pointer to the new copy
 */
void copyList(int* temp, int* newList, int length)
{
   int i;
   for(i = 0; i < length; i++)
   {
      newList[i] = temp[i];
   }
}
