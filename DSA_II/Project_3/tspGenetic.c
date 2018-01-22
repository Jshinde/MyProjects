/**
 * After recieving a list of cities with weighted edges, this program uses a generational technique to find the optimal path. 
 * 
 * @author Daniel Belcher 
 * @author Joshua Shinde
 * @date 4/12/2017
 * @info Course COP3014
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "helper.h"
#include "tspGenetic.h"

int main(int argc, char** argv)
{
   if(argc == 6)
   {
      int i = 0;
      char* filename = argv[1];
      int numCity = atoi(argv[2]);
      int numGen = atoi(argv[3]);
      int numTours = atoi(argv[4]);
      double percent = atof(argv[5]);
      struct timespec starttime, endtime;
	  
      GraphT* mainGraph = readFile(numCity, filename);
      if (mainGraph == NULL) {
           printf ("unable to read the file");
           return 1;
      }

      clock_gettime(CLOCK_REALTIME, &starttime);
      int** tourList = malloc(sizeof(int) * numCity);
      
      while(i < numTours)
      {
         tourList[i] = malloc(sizeof(int) * numCity);
         i++;
      }
      
      i = 0;
      int j = 0;
      int x = numTours / percent;
      
      while(i < numCity)
      {
         tourList[0][i] = i;
      }
      
      i = 1;
      
      while(i < numTours)
      {
         tourList[1] = mutate(tourList[i - 1], numCity);
      }
      
      sortList(tourList, (numTours / 2) + 1, numCity, mainGraph);
      
      while(i < numGen)
      {
         while(j < x)
         {
            tourList[numTours - j + 1] = mutate(tourList[i], numCity);
            j++;
         }
         
         j = 0;
         sortList(tourList, (numTours / 2) + 1, numCity, mainGraph);
         i++;
      }
	  
	  //Final data collection
	  //float timespent = stopTimer(starttime);
	  clock_gettime(CLOCK_REALTIME, &endtime);
	  float time_elapsed = (1E9 * (endtime.tv_sec - starttime.tv_sec) + (endtime.tv_nsec - starttime.tv_nsec)) / 1E9;

	  int* lowCost= malloc(sizeof(int) * numCity);
	  copyList(tourList[0], lowCost, numCity);
	  
	  
	  //Print results of program
		printf("Final Solution List: ");
		i =0; 
		while(i < numCity)
		{
			printf("%c", mainGraph->list[(lowCost[i])]);
			i++;
		}
		printf("/nFinal Solution Cost: %d", checkCost(lowCost, mainGraph));
		printf("Final Solution Time: %f", (float) time_elapsed);
   }
   else
      printf("Improper Arguments on Command Line");
   
   return 0;  
}


/**
 * Mutates the path passed to it and returns a new path
 *
 * @param ogList list to be mutated 
 * @param length how long the path is
 *
 * @return the error code, 0 represents success and -1 represents failure
 */
int* mutate(int* ogList, int length)
{
   int* tempList = malloc(sizeof(int) * length);
   copyList(ogList, tempList, length);
   swapSpots(tempList,(rand() % length), (rand() % length));

   return(tempList);
}


/**
 * Sorts the list of paths currently passed
 *
 * @param tempList list to be sorted 
 * @param numTour variable representing number of paths in list
 * @param length length of each path
 * @param mainGraph graph used to determine weight of each path
 *
 * @return the error code, 0 represents success and -1 represents failure
 */
void sortList(int** tempList, int numTour, int length, GraphT* mainGraph)
{
   int maxCost = INT_MAX;
   int i = 0;
   int j = 0;
   int y = 0;
   int *temp;
   
   while(i < numTour)
   {
      while(j < length)
      {
         if(maxCost > checkCost(tempList[j], mainGraph))
         {
            y = j;
         }
         j++;
      }    
      temp = tempList[i];
      tempList[i] = tempList[y];
      tempList[y] = temp;
      i++;
      j = y = i;
   }   
}

