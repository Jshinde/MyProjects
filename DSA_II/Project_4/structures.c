/**
 * File full of helper functions for binPacking.c
 * 
 * @author Daniel Belcher 
 * @author Joshua Shinde
 * @date 4/30/2017
 * @info Course COP3014
 */
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
 
BinT* createBin(float sizeMax)
{
	BinT* temp;
	temp = malloc(sizeof(BinT));
	temp->contents = NULL;
	temp->nextBin  = NULL;
	
	temp->size = sizeMax;
	return(temp);
}

void destroyBins(BinT* temp)
{
	//recursive piece to destroy whole list
	if(temp->nextBin != NULL)
	{
		destroyBins(temp->nextBin);
	}
	destroyObjects(temp->contents);
	free(temp);
}

ObjectT* createObject(float sizeTemp)
{
	ObjectT* temp;
	temp = malloc(sizeof(ObjectT));
	temp->nextObject = NULL;
	temp->prevObject = NULL;
	
	temp->size = sizeTemp;
	return(temp);	
}

void destroyObjects(ObjectT* temp)
{
	//recursive piece to empty the list
	if(temp->nextObject != NULL)
	{
		destroyObjects(temp->nextObject);
	}
	free(temp);
}


ObjectT* sortList(ObjectT* oldList, float count)
{
	int i;
	float *newArray;
	newArray = malloc(sizeof(float) * count);
	ObjectT* current;
	ObjectT* newList;
	current = oldList;
	
	for(i = 0; i < count; i++)
	{
		newArray[i] = current->size;
		current = current->nextObject;
	}
	
	destroyObjects(oldList);
	newList = createObject(newArray[0]);
	current = newList;
	
	for(i = 1; i < count; i++)
	{
		current->nextObject = createObject(newArray[i]);
		current = current->nextObject;
	}
	
	return(newList);
}

void firstFit(BinT* startBin, ObjectT* objectList, float binMaxSize)
{
	BinT*     currentBin = startBin;
	ObjectT*  currentObject;
	
	while(objectList != NULL)
	{
		//if the bin can fit the object
		if(((currentBin->size) - (objectList->size)) >= 0)
		{
			//if there are no objects in the bin yet
			if(currentBin->contents == NULL)
			{
				currentBin->contents = createObject(objectList->size);
				currentBin->size -= objectList->size;
			}
			//else if it has some contents
			else
			{
				currentObject = currentBin->contents;
				while(currentObject->nextObject != NULL)
				{
					currentObject = currentObject->nextObject;
				}
				//loop above finds end of list
				currentObject->nextObject = createObject(objectList->size);
				currentBin->size -= objectList->size;
			}
			objectList = objectList->nextObject;
			currentBin = startBin;
		}
		//else if bin can't fit it
		else
		{
			//if there isn't a next bin in list
			if(currentBin->nextBin == NULL)
			{
				currentBin->nextBin = createBin(binMaxSize);
				currentBin = currentBin->nextBin;
			}
			//else if there is a next bin
			else
			{
				currentBin = currentBin->nextBin;
			}
			//then the while loop goes again without skipping an object
		}
	}
}

void nextFit(BinT* currentBin, ObjectT* objectList, float binMaxSize)
{
	ObjectT*  currentObject;
	
	while(objectList != NULL)
	{
		//if the bin can fit the object
		if(((currentBin->size) - (objectList->size)) >= 0)
		{
			//if there are no objects in the bin yet
			if(currentBin->contents == NULL)
			{
				currentBin->contents = createObject(objectList->size);
				currentBin->size -= objectList->size;
			}
			//else if it has some contents
			else
			{
				currentObject = currentBin->contents;
				while(currentObject->nextObject != NULL)
				{
					currentObject = currentObject->nextObject;
				}
				//loop above finds end of list
				currentObject->nextObject = createObject(objectList->size);
				currentBin->size -= objectList->size;
			}
			objectList = objectList->nextObject;
		}
		//else if bin can't fit it
		else
		{
			currentBin->nextBin = createBin(binMaxSize);
			currentBin = currentBin->nextBin;
		}
	}
}

void bestFit(BinT* startBin, ObjectT* items, float binMaxSize)
{
	ObjectT* currentObject;
	BinT* currentBin;
	BinT* bestBin;
	BinT* lastBin;
	bestBin = NULL;
	currentBin = startBin;
	float bestRemainder = binMaxSize;

	//loop through all objects in list
	while(items != NULL)
	{
		while(currentBin != NULL)
		{
			//if it fits in the current bin
			if(((currentBin->size) - (items->size)) >= 0)
			{
				//if this bin is a better fit than best bin
				if(bestRemainder >= (currentBin->size - items->size))
				{
					bestRemainder = (currentBin->size - items->size);
					bestBin = currentBin;
					lastBin = currentBin;
					currentBin = currentBin->nextBin;
				}
				//if it isn't better than best bin
				else
				{
					lastBin = currentBin;
					currentBin = currentBin->nextBin;
				}
			}
			//if it doesn't fit in the bin
			else
			{
				lastBin = currentBin;
				currentBin = currentBin->nextBin;
			}
		}
		//if we found a perfect fit for it
		if(bestBin != NULL)
		{
			//if there are no objects in the bin yet
			if(bestBin->contents == NULL)
			{
				bestBin->contents = createObject(items->size);
				bestBin->size -= items->size;
			}
			//else if it has some contents
			else
			{
				currentObject = bestBin->contents;
				while(currentObject->nextObject != NULL)
				{
					currentObject = currentObject->nextObject;
				}
				//loop above finds end of list
				currentObject->nextObject = createObject(items->size);
				bestBin->size -= items->size;
			}
		}
		//didn't fit so we make a new bin
		else
		{
			lastBin->nextBin = createBin(binMaxSize);
			lastBin = lastBin->nextBin;
			lastBin->contents = createObject(items->size);
			lastBin->size -= items->size;
		}

		//reset everything for loop and next object
		currentBin = startBin;
		bestBin = NULL;
		bestRemainder = binMaxSize;
		items = items->nextObject;
		
	}
}

int binCount(BinT* binList)
{
	int x = 0;
	while(binList != NULL)
	{
		binList = binList->nextBin;
		x++;
	}
	return(x);
}

void printBins(BinT* bins)
{
	int x = 1;
	ObjectT* temp;
	while(bins != NULL)
	{
		printf("Bin %d: ", x);
		x++;
		temp = bins->contents;
		while(temp != NULL)
		{
			printf("%4.2f -> ", temp->size);
			temp = temp->nextObject;
		}
		printf("\n");
		bins = bins->nextBin;
	}
}
