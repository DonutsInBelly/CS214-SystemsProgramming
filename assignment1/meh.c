#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include "mymalloc.h"

char *byte[3000];
void *arr[3000];

int main(){

	time_t sum = 0;
	int ex;

	for(ex = 0; ex < 100; ex++){

		/*
		free(byte[0]);
		*/

		time_t currRun;
		time(currRun);

		// Test Case A: malloc() 1 byte 3000 times, then free() the 3000 1 byte pointers one by one
		int i;
		for(i = 0; i < 30; i++){

			arr[i] = malloc(1);
		}

		for(i = 0; i < 3000; i++){

			free(byte[i]);
		}

		printf("--------------------------------\n");

		//Test Case B: malloc() 1 byte and immediately free it 3000 times in a row
		byte[0] = (char*)malloc(sizeof(char));

		i = 0;

		while(i < 3000){
			free(byte[0]);
		}

		printf("--------------------------------\n");


		//Test Case C: Randomly choose between a 1 byte malloc() or free() 6000 times
		int count = 0;
		int freeCount = 0;

		while(count <= 3000){

			int x = rand();

			if(x % 2 == 0){

				while(freeCount <= 6000){

					free(byte[0]);
					freeCount++;
				}

				freeCount = 0;

			}

			else{

				malloc(byte[0]);
				count++;
			}

		}

		free(byte[0]);

		printf("-----------------------------------------------------------------\n");

		//Test Case D:  Randomly choose between a randomly-sized malloc() or free 6000 times

		count = 0;
		freeCount = 0;
		int mallocAmt = 0;
		int x = 0;
		char byte2;

		while(count <= 3000){

			x = rand();

			if(x % 2 == 0){

				while(freeCount <= 6000){

					free(byte2);
					freeCount++;
				}

				freeCount = 0;

			}

			else{

				while(mallocAmt == 0 || mallocAmt > 4996){
					mallocAmt = rand();

				}
					byte2 = malloc(mallocAmt);
					count++;
			}

		}

		free(byte2);

		printf("-------------------------------------\n");

		//Case E: Overload.

		byte2 = malloc(1000000);

		free(byte2);

		printf("------------------------------------------------\n");

		//F: Size 0 malloc

		byte2 = malloc(0);

		free(byte2);

		currRun = time(currRun);

		sum = sum + currRun;
	}

	//Computing the average run time

	sum = sum/100;

	printf("%d\n",sum);

}
