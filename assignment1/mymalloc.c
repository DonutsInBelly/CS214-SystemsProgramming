#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE = 5000
#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )

static char myBlock[MAX_SIZE];
static unsigned int callCounter = 0;
static unsigned int lastAssigned = 0;

void *malloc(size_t size) {

	// if malloc if being run for the first time, flood block with -1
	if(callCounter==0) {
		for (size_t i = 0; i < MAX_SIZE; i++) {
			myBlock[i] = -1
		}
	}
	callCounter++;

	// Check if input is too large or 0
	if(size > MAX_SIZE - sizeof(int) || size == 0){
		return null;
	}

	// search for open space in block
	for (size_t i = 0; i < MAX_SIZE; i++) {
		// if index available
		// -1 denotes first allocation
		if (myBlock[i]==-1) {
			myBlock[i] = size;
			lastAssigned = i;
			return &myBlock[i+4];
		}

		// if current slot has data in front of it, but this one is free
		if(myBlock[i]<0) {
			int slotSize = abs(myBlock[i]) - i;
		}
	}

	int i = 0;

	//Check the num value from each allocation value

	while(arr[i] > 0 || (arr[i] < 0 && arr[i] < -size) || i > 4999){

		if(i < 0){

			i = -arr[i] + i;
			continue;
		}

		i = arr[i] + i;
	}

	if( (i + sizeof(int) + size) > 4999){
		return null;
	}

	int *num = (int*) (&arr[i]);
	num = size;

	return num++;

}

void free(void *ptr){

	int *ptrInt = (int*) (&ptr);
	ptrInt--;

	if( *ptrInt <= 0){
		return;
	}

	if( &arr[0] > ptrInt < &arr[4999]){
		return;
	}

	ptrInt = -1 * *ptrInt;
	return;

}
