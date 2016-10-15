#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 5000
static char myBlock[MAX_SIZE];
#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )

void *mymalloc(size_t size) {

	printf("Start of method\n");
	static unsigned int callCounter = 0;
	int * metaData = (int*)(&myBlock[0]);

	if(callCounter == 0) {
		size_t i;
		printf("Entered callCounter = 0 if statement.\n");
		for (i = 0; i <= 1250; i = i + 4){
			
			metaData = (int*)(&myBlock[i]);
			*metaData = 0;

		}
		printf("Finished the callCounter loop.\n");
	}
	callCounter++;

	// Check if input is too large or 0
	if( (size > MAX_SIZE - sizeof(int)) || size == 0){
		printf("Too big or 0 size\n");
		return NULL;
	}

	metaData = (int*)(&myBlock[0]);
	size_t i = 0;
	
	while(i < MAX_SIZE){

		metaData = (int*)(&myBlock[i]);

		if( *metaData < 0 && *metaData <= -(size +8)){
			printf("Metadata is negative\n");
			*metaData = size;
			int *ptr = (&myBlock[i +size])
			*ptr = 0;	
			return &myBlock[i+4];
		}

		if( *metaData == 0 && 4999 - i >= size + 8){
			printf("Metadata = 0\n");
			*metaData = size;
			int *ptr = (&myBlock[i +size])
			*ptr = 0;
			return &myBlock[i+4];
		}

		if(*metaData > 0){
			printf("Metadata > 0: %d\n", *metaData);
			i = i + *metaData;
		} 
	}

	return NULL;
}

void myfree(void *ptr){
	
	int *ptrInt;
	
	//Store the first piece of data. +4 to skip metadata.
	int i;
	int size;
	
	for(i = 4; i < MAX_SIZE; i = i + size){
	
		if(ptr == &myBlock[i]){
			*ptrInt = *ptrInt * -1;
			return;
		}

		ptrInt = (int*)(&myBlock[i-4]);

		if(*ptrInt == 0){
			return;
		}

		size = *ptrInt;

	}

	return;
}
