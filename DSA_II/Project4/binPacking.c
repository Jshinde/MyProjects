/**
 * Main file that attempts the bin packing problem using three algorithmic attempts
 * 
 * @author Daniel Belcher 
 * @author Joshua Shinde
 * @date 4/30/2017
 * @info Course COP3014
 */

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

int main(int argc ,char* argv[])
{
	char* filename;
	filename = argv[1];
	if(argv[1] == NULL)
	{
		printf("No file given");
		return 1;
	}
	
	//file check and error code here
	FILE* filep;
	filep = fopen(filename, "r");
	if(filep == NULL)
	{
		printf("Incorrect filename.");
		return(1);
	}
	
	float binMaxSize, objectTemp;
	ObjectT* topOfList;
	ObjectT* currentList;
	
	//Loop to read all objects from the file
	fscanf(filep, "%f", &binMaxSize);
	while(!feof(filep))
	{
		fscanf(filep, "%f", &objectTemp);
		if(objectTemp > binMaxSize)
		{
			printf("Object was larger than bin size, ignoring.\nSize: %4.2f\n", objectTemp);
		}
		else
		{
			//if this is the first object
			if(topOfList == NULL)
			{
				topOfList = createObject(objectTemp);
				currentList = topOfList;
			}
			//if not first object
			else
			{
				currentList->nextObject = createObject(objectTemp);
				currentList->nextObject->prevObject = currentList;
				currentList = currentList->nextObject;
			}
		}
	}
	
	float objectCount;
	currentList = topOfList;
	while(currentList != NULL)
	{
		objectCount++;
		currentList = currentList->nextObject;
	}
	
	//Creating all Bins for different types of algorithm
	BinT* onlineFirst  = createBin(binMaxSize);
	BinT* onlineNext   = createBin(binMaxSize);
	BinT* onlineBest   = createBin(binMaxSize);
	BinT* offlineFirst = createBin(binMaxSize);
	BinT* offlineBest  = createBin(binMaxSize);

	//Doing all the bin algorithms for online
	firstFit(onlineFirst, topOfList, binMaxSize);
	nextFit(onlineNext, topOfList, binMaxSize);
	bestFit(onlineBest, topOfList, binMaxSize);

	//sort list
	currentList = sortList(topOfList, objectCount);

	//Doing all bin algorithms for offline
	firstFit(offlineFirst, currentList, binMaxSize);
	bestFit(offlineBest, currentList, binMaxSize);
	
	//free up the space the object list uses
	destroyObjects(currentList);
	
	//Print block for chart
	printf("------------------------------\n");
	printf("------------------------------\n");
	printf("| Style   | Number of Bins   |\n");
	printf("------------------------------\n");
	printf("| Online  |                  |\n");
	printf("| First   |      %3d         |\n", binCount(onlineFirst));
	printf("| Next    |      %3d         |\n", binCount(onlineNext));
	printf("| Best    |      %3d         |\n", binCount(onlineBest));
	printf("------------------------------\n");
	printf("| Offline |                  |\n");
	printf("| First   |      %3d         |\n", binCount(offlineFirst));
	printf("| Best    |      %3d         |\n", binCount(offlineBest));
	printf("------------------------------\n");
	printf("------------------------------\n\n");
	
	//print block for all bin layouts then we free the space
	//Online First Bins
	printf("Online Fist:\n");
	printBins(onlineFirst);
	destroyBins(onlineFirst);
	
	//Online Next Bins
	printf("Online Next:\n");
	printBins(onlineNext);
	destroyBins(onlineNext);
	
	//Online Best Bins
	printf("Online Best:\n");
	printBins(onlineBest);
	destroyBins(onlineBest);
	
	//Offline First Bins
	printf("Offline Fist:\n");
	printBins(offlineFirst);
	destroyBins(offlineFirst);
	
	//Offline Best Bins
	printf("Offline Best:\n");
	printBins(offlineBest);
	destroyBins(offlineBest);
	
	return(0);
}
