#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

void insertionsort(char** array, int strMax) {
	char* current;
	int position;
	for (int i = 1; i < strMax; i++) {
		current = (char*)malloc(sizeof(array[i]));
		strcpy(current, array[i]);
		position = i;
		while ( (position>0) && (strcasecmp(array[position-1], current)>0) ) {
			strcpy(array[position], array[position-1]);
			--position;
			printf(" item moved : %s\n" , array[position]);
		}
		printf(" item inserted : %s, at position : %d\n" , current,position);
		strcpy(array[position], current);

		printf("Iteration: %d\n", i);
		for (int i = 0; i < strMax; i++) {
			printf("%s\n", array[i]);
		}
	}
}

int main(int argc, char** argv) {
	// Check that user isn't entering bullshit like more than one argument.
	if(argc != 2) {
		printf("Please use only 1 argument.\ni.e. ./pointersorter \"the*string*of*some*sort\"\nExiting...\n");
		return 1;
	}

	/* input is the string that we're handling.
	* maxSize is the max number of "words" that can appear in an argument.
	* Theory is that a string can contain at most the ceiling of half its length.
	* Like if a string is half non alphabet letters.
	* ex: "a*a*a*a"
	*/
	char* input = argv[1];
	int maxSize = (int)ceil(((double)strlen(input))/2)+1;
	printf("Max Size of Array: %d\n", maxSize);
	//char* strArray[maxSize]; // = { NULL }; // Initialize all elements in array to null
	char** strArray = (char**)malloc(maxSize*sizeof(char*));
	int currentstrArray = 0;
	int wordStart = 0;
	int wordEnd;
	for (wordEnd = 0; wordEnd <= strlen(input)-1; wordEnd++) {
		printf("index %d : %c\n", wordEnd, input[wordEnd]);
		// If the current char isn't a alphabet letter
		if(!isalpha(input[wordEnd])) {
			// Handles case where first character isn't an alphabet letter
			if(wordEnd == 0) {
				wordStart = 1;
				printf("wordStart: %d\n", wordStart);
				continue;
			} else if( (!isalpha(input[wordEnd-1])) && (wordEnd==strlen(input)-1) ) { // handles case where there's multiple non alphabet letters at the end
				// prevents overcounting
				currentstrArray--;
				printf("%s\n", "Ending");
				break;
			} else if(!isalpha(input[wordEnd-1])) { // handles case where there's multiple non alphabet letters
				wordStart = wordEnd+1;
				printf("%s\n", "Multiple no alphas\n");
				continue;
			} else if(wordEnd == strlen(input)-1) { // handles case where current char is non alphabet letter, but is the last char in input
				int subLength = wordEnd-wordStart+1;
				printf("Substring Length: %d\n", subLength);
				char subStr[subLength];
				strncpy(subStr, &input[wordStart], subLength-1);
				subStr[subLength-1] = '\0'; // add null terminating byte
				printf("Substring: %s\nSubstring length: %zd\n", subStr, strlen(subStr));
				// Assign new string to a spot on strArray.
				strArray[currentstrArray] = malloc(sizeof(subStr));
				strcpy(strArray[currentstrArray], subStr);
				printf("inserting string: %s at index: %d\n", strArray[currentstrArray], currentstrArray);
				break;
			}
			// Case where we've found the end of a new word. Create a substring first.
			int subLength = wordEnd-wordStart+1;
			printf("Substring Length: %d\n", subLength);
			char subStr[subLength];
			strncpy(subStr, &input[wordStart], subLength-1);
			subStr[subLength-1] = '\0'; // add null terminating byte
			printf("Substring: %s\nSubstring length: %zd\n", subStr, strlen(subStr));
			// Assign new string to a spot on strArray.
			strArray[currentstrArray] = malloc(sizeof(subStr));
			strcpy(strArray[currentstrArray], subStr);
			printf("inserting string: %s at index: %d\n", strArray[currentstrArray], currentstrArray);
			currentstrArray++;
			// set the start of a new word to be the next char
			wordStart = wordEnd+1;
			continue;
		} else if(wordEnd==strlen(input)-1) {
			printf("%s\n", "ending\n");
			// Case where we've found the end of a new word. Create a substring first.
			int subLength = wordEnd-wordStart+2;
			printf("Substring Length: %d\n", subLength);
			char subStr[subLength];
			strncpy(subStr, &input[wordStart], subLength-1);
			subStr[subLength-1] = '\0'; // add null terminating byte
			printf("Substring: %s\nSubstring length: %zd\n", subStr, strlen(subStr));
			// Assign new string to a spot on strArray.
			strArray[currentstrArray] = malloc(sizeof(subStr));
			strcpy(strArray[currentstrArray], subStr);
			printf("inserting string: %s at index: %d\n", strArray[currentstrArray], currentstrArray);
			break;
		}

	}
	// Insertion sort algorithm
	insertionsort(strArray, currentstrArray+1);
	// Print out results
	printf("\n\n\n\n\n\n");
	for (int i = 0; i <= currentstrArray; i++) {
		printf("Index: %d\n", i);
		printf("%s\n", strArray[i]);
	}
	printf("Length: %ld\n", strlen(input));
}
