#include <stdio.h>
#include <stdlib.h>

static char myBlock[5000];

void malloc(size_t size) {
	  
	if(size == 0){
		return null;
	}
	
	if(size > 5000 - sizeof(int) ){
		return null;
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
