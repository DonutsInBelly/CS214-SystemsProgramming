#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 5000
#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )

static char myBlock[MAX_SIZE];

void *mymalloc(size_t size) {
	static unsigned int callCounter = 0;
	static unsigned int lastAssigned = 0;

	// if malloc if being run for the first time, flood block with -1
	if(callCounter==0) {
		size_t i;
		for (i = 0; i < MAX_SIZE; i++) {
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
		printf("Current Slot Index: %d value in myBlock: %d\n", i, myBlock[i]);
		// if index is non-negative and has a value, this slot is allocated
		if(myBlock[i]!=-1) {
			i = myBlock[i];
			printf("Moving to next slot at address: 0x%02X at index: %d\n", &myBlock[i], myBlock[i]);
			continue;
		}
		// if index available
		// -1 denotes first allocation
		if (myBlock[i]==-1) {
			// puts index of next Metadata location in this index
			myBlock[i] = (i + 4 + size);
			printf("Predicted next index: %d\n", i + 4 + size);
			printf("Metadata index: %d, next slot index: %d\n", i, myBlock[i]);
			lastAssigned = i;
			printf("Metadata Location: 0x%02X\nAllocating %d bits at address: 0x%02X, with index: %d\nNext slot is: 0x%02X with index %d\n", &myBlock[i], size, &myBlock[i+4], i+4, &myBlock[i+4+size], myBlock[i]);
			int next=i+4+size;
			myBlock[i]=next;
			return &myBlock[i+4];
		}

		// if current slot has data in front of it, but this one is free
		if(myBlock[i]<0) {
			// determines how much space we have to work with at this index
			int slotSize = abs(myBlock[i]) - i;
			// if theres not enough space, continue to the next slot
			if(slotSize<size) {
				i = abs(myBlock[i]);
				printf("Previously Allocated, moving to new index at %d\n", i);
				continue;
			}
			// Show this slot has been allocated and return this slot
			myBlock[i] *= -1;
			printf("Reallocating this slot at index: %d next index at: %d\n", i, myBlock[i]);
			return &myBlock[i+4];
		}
	}
	printf("No space available in block\n");
	return NULL;
}

void myfree(void *ptr){
	//printf("Trying to free: 0x%02X\nFirst Index: %d\n", ptr, myBlock[0]);
	int i = 0;
	// Loop through block to see if the given address is a valid one
	while (i < MAX_SIZE && i!=-1) {
		if(i < -1) {
			i *= -1;
		}
		//printf("Testing address: 0x%02X\n", &myBlock[i+4]);
		if(&myBlock[i+4] == ptr) {
			//printf("Address found: 0x%02X at index: %d\n", &myBlock[i], i);
			// If slot is already allocated
			if(myBlock[i]<0) {
				//printf("This address has already been freed. Returning NULL.\n");
				return NULL;
			} else {
				// Make the slot unallocated
				//printf("Freeing index: %d and returning.\nNext slot: %d\n", i-4, myBlock[i]);
				myBlock[i] *= -1;
				return;
			}
		}
		// Move to next slot
		//printf("Moving to slot: %d\n", myBlock[i]);
		i = myBlock[i];
	}
	// This means the address given to us isn't valid.
	//printf("Address not found in block. Returning NULL.\n");
	return NULL;
}
