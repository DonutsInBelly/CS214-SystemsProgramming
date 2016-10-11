#include <stdio.h>
#include <stdlib.h>

static char myBlock[5000];

void malloc(size_t size) {
	  
	if(size == 0){
		return null;
	}
	
	if(size > 5000 - /*size of metadata*/){
		return null;
	}

	int i = 0;

	while(arr[i] > 0 || (arr[i] < 0 && arr[i] < -size) || i > 4999){
		i = arr[i] + i;
	}

	if( (i + /*size of metadata*/ + size) > 4999){
		return null;
	}

	//Loop through each array index and put each bit into thier indices. 
	int *num = (int*) (&arr[i]);
	num = size;

	return int *num + 4;
	
}

void free(void *ptr){
	
	int *ptrInt = (int*) (&ptr);
	ptrInt--;

	

	return;
	//if unallocated, error
	//if not address, error
	//

}
