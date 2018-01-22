/**
 * After recieving a list of cities with weighted edges, this program uses a permutation technique to find the optimal path. 
 * 
 * @author Daniel Belcher 
 * @author Joshua Shinde
 * @date 4/12/2017
 * @info Course COP3014
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "helper.h"
void permute(int *tempList,int *lowCost, int location, int length, GraphT* g);

int main(int argc, char* argv[])
{
   if(argc == 3)
   {
      char *filename = argv[1];
      int numCity = atoi(argv[2]);
      struct timespec starttime, endtime;

      //Creation of graph structure and initialization of list of cities
      GraphT* mainGraph	= readFile(numCity, filename);

      if(mainGraph->list[0] == -1)
      {
         printf("File did not exist, graph not made.");
         return(0);
      }
   	int sample[numCity];
   	int lowCost[numCity];
   	
   	int i = 0;
   	while(i < numCity)
   	{
   		sample[i] = i;
   		i++;
   	}
   	
   	i = 0;
   	while(i < numCity)
   	{
   		lowCost[i] = i;
   		i++;
   	}
	
	clock_gettime(CLOCK_REALTIME, &starttime);
   	//Labor intensive mutations till optimal solution is found

   	permute(sample, lowCost, 0, numCity, mainGraph);

	clock_gettime(CLOCK_REALTIME, &endtime);
	float time_elapsed = (1E9 * (endtime.tv_sec - starttime.tv_sec) + (endtime.tv_nsec - starttime.tv_nsec)) / 1E9;

	//Print results of program
	printf("Final Solution List: ");
	i =0; 
	while(i < numCity)
	{
		printf("%c", mainGraph->list[(lowCost[i])]);
		i++;
	}
	printf("\nFinal Solution Cost: %d\n", checkCost(lowCost, mainGraph));
	printf("Final Solution Time: %f", (float) time_elapsed);
	
	
   	free(sample); free(lowCost);
	
   	return(0);
   }
   else
   {
      printf("Incorrect ammount of command line arguments.");
      return(0);
   }
}

/**
 * recursive function that makes permutations of a path until no more are possible
 *
 * @param tempList path to make permutations of 
 * @param lowCost the lowest cost path to be made
 * @param location how far into the path we have made permutations
 * @param length how long the path is
 * @param g the graph we get the value of the path from
 *
 * @return nothing but an error code if it breaks
 */
void permute(int *tempList,int *lowCost, int location, int length, GraphT* g)
{
   int i;
   if(location == length)
   {
         return;
   }
   else
   {
         for(i = 1; (i + location) < length - 1; i++)
         {  
               swapSpots(tempList, location, (location + i));
               if(checkCost(tempList, g) < checkCost(lowCost, g))
               {
                  printf("Before copylist\n");
		  copyList(tempList, lowCost, length);
		  printf("after copylist\n");
               }
               permute(tempList, lowCost, (location + i), length, g);
               swapSpots(tempList, location, (location + i));
         }
   }
}
