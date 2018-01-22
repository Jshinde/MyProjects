/**
 * File full of helper structures and prototypes for the functions in structures.c
 * 
 * @author Daniel Belcher 
 * @author Joshua Shinde
 * @date 4/30/2017
 * @info Course COP3014
 */

typedef struct ObjectT
{
	float size;
	struct ObjectT *nextObject;
	struct ObjectT *prevObject;
	
}ObjectT;

typedef struct BinT
{
	float size;
	ObjectT* contents;
	struct BinT* nextBin;
	int numBins;
}BinT;

/**
 * Allocates space for a new Bin structure 
 *
 * @param sizeMax size of bin
 *
 * @return the created Bin
 */
BinT* createBin(float sizeMax);

/**
 * Frees the Bin List passed to it
 *
 * @param temp a pointer to the first Bin in a list that is to be freed
 *
 * @return nothing
 */
void destroyBins(BinT* temp);

/**
 * Allocates memory for a new object structure
 *
 * @param sizeTemp size of object to be created
 *
 * @return the error code, 0 represents success and -1 represents failure
 */
ObjectT* createObject(float sizeTemp);

/**
 * Frees the object list passed to it
 *
 * @param temp the object list taht will be freed
 *
 * @return nothing
 */
void destroyObjects(ObjectT* temp);

/**
 * Sorts an object list passed to it 
 *
 * @param oldList the object pointer for the unsorted list 
 *
 * @return the sorted object list pointer
 */
ObjectT* sortList(ObjectT* oldList, float count);

/**
 * First Fit Algorithm for bin sorting
 *
 * @param startBin the firs tbin pointer in the list
 * @param objectList the list of objects to be put in the bin
 * @param binMaxSize the max size for new bins
 *
 * @return the error code, 0 represents success and -1 represents failure
 */
void firstFit(BinT* startBin, ObjectT* objectList, float binMaxSize);

/**
 * Next Fit Algorithm for bin sorting
 *
 * @param startBin the firs tbin pointer in the list
 * @param objectList the list of objects to be put in the bin
 * @param binMaxSize the max size for new bins
 *
 * @return the error code, 0 represents success and -1 represents failure
 */
void nextFit(BinT* currentBin, ObjectT* objectList, float binMaxSize);

/**
 * Best Fit Algorithm for bin sorting
 *
 * @param startBin the firs tbin pointer in the list
 * @param objectList the list of objects to be put in the bin
 * @param binMaxSize the max size for new bins
 *
 * @return the error code, 0 represents success and -1 represents failure
 */
void bestFit(BinT* startBin, ObjectT* items, float binMaxSize);

/**
 * Counts how many bins are in the passed linked list 
 *
 * @param binList the list of bins we are counting
 *
 * @return the number of bins
 */
int binCount(BinT* binList);

/**
 * Prints the bin list that was passed to the function
 *
 * @param bins linked list of bins to be printed to screen
 *
 * @return the error code, 0 represents success and -1 represents failure
 */
void printBins(BinT* bins);
