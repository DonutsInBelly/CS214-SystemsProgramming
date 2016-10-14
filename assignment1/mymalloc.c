#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 5000

void *mymalloc(size_t size) {

	static char myBlock[MAX_SIZE];
	static unsigned int callCounter = 0;
	static unsigned int lastAssigned = 0;
	// if malloc if being run for the first time, flood block with -1
	if(callCounter==0) {
		for (size_t i = 0; i < MAX_SIZE; i++) {
			myBlock[i] = -1;
		}
	}
	callCounter++;

	// Check if input is too large or 0
	if(size > MAX_SIZE - sizeof(int) || size == 0){
		return NULL;
	}

	size_t i = 0;
	// search for open space in block
	while (i < MAX_SIZE) {
		printf("Current Block Index: %d\n", i);
		// if index is non-negative and has a value, this slot is allocated
		if(myBlock[i]>0) {
			i = myBlock[i];
			printf("Moving to next block at address: 0x%02X\n", &myBlock[i]);
			continue;
		}
		// if index available
		// -1 denotes first allocation
		if (myBlock[i]==-1) {
			// puts index of next Metadata location in this index
			myBlock[i] = i + 4 + size;
			lastAssigned = i;
			printf("Metadata Location: 0x%02X\nAllocating %d bits at address: 0x%02X, with index: %d\nNext block is: 0x%02X with index %d\n", &myBlock[i], size, &myBlock[i+4], i+4, &myBlock[i+4+size], i+4+size);
			return &myBlock[i+4];
		}

		// if current slot has data in front of it, but this one is free
		if(myBlock[i]<0) {
			int slotSize = abs(myBlock[i]) - i;
		}
	}
}

void free(void *ptr){
/*
	int *ptrInt = (int*) (&ptr);
	ptrInt--;

	if( *ptrInt <= 0){
		return;
	}

	if( &arr[0] > ptrInt < &arr[4999]){
		return;
	}

	ptrInt *= -1;
	return;
*/
}
