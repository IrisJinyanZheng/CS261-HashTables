
#define _CRT_SECURE_NO_WARNINGS

#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */

/* Code Source Cited: 
URL: http://stackoverflow.com/questions/7700400/whats-a-good-hash-function-for-english-words

I have copied this code from stack exchange to ensure that my Hash Map would hash quickly into an 
appropriate number of buckets for a larger set of links (ie. the english language). 

The code includes a "seed", and a hash equation
*/
unsigned long hashstring(unsigned char *str) {
	unsigned long hash = 5381;
	int c;

	while (c = *str++) {
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	}

	return hash;
}

void loadDictionary(FILE* file, HashMap* map)
{
    // FIXME: implement
	char * word = nextWord(file);

	while (word != NULL) {
		
		// Compute hash value
		unsigned long hash = hashstring(word);

		if (hashMapContainsKey(map, word)) {
			// Word in dictionary already
		}
		else {
			// Add word to dictionary 
			hashMapPut(map, word, hash);
		}
		free(word);
		word = nextWord(file);
	}

	//printf("printing dictionary\n");
	//hashMapPrint(map);
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{


    // FIXME: implement
    HashMap* map = hashMapNew(1000);
    
    FILE* file = fopen("dictionary.txt", "r");
	// If file not found
	if (file == NULL) {
		perror("Error");
	}
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
    
    char inputBuffer[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);
        
        // Implement the spell checker code here..
		if (hashMapContainsKey(map, inputBuffer)) {
			printf("That word is spelled correctly!\n");
		}
		else {
			printf("That word is mispelled!\n");
		}
        
        if (strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
        }
    }
    
    hashMapDelete(map);
    return 0;
}