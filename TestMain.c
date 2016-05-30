

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int main() {

	printf("Meow");
	int capacity = 10;
	HashLink links[] = {
		{.key = "a",.value = 0,.next = NULL },
		{.key = "c",.value = 1,.next = NULL },
		{.key = "d",.value = 2,.next = NULL },
		{.key = "f",.value = 3,.next = NULL },
		{.key = "g",.value = 4,.next = NULL }
	};
	const char* notKeys[] = { "b", "e", "h" };

	HashMap * map = hashMapNew(capacity);

	/* Testing Put */
	for (int i = 0; i < 5; i++) {
		hashMapPut(map, links[i].key, links[i].value);
		hashMapPrint(map);
	}

	printf("Val with key 'a' = %d\n", *hashMapGet(map, links[0].key));
	
	/* Testing Get */
	if (hashMapGet(map, notKeys[0]) == NULL) {
		printf("Val with key 'b' not in map \n");
	}

	int newCap = 20;

	hashMapPut(map, links[0].key, 10);
	hashMapPrint(map);

	hashMapPut(map, "z", 10);
	hashMapPrint(map);

	/* Testing Resize */
	resizeTable(map, newCap);

	/* Testing Contains */
	printf(" T/F: contains A: %d\n", hashMapContainsKey(map, "a"));
	printf(" T/F: contains B: %d\n", hashMapContainsKey(map, "b"));


	/* Testing Remove */
	hashMapRemove(map, "b"); // Not in map
	hashMapRemove(map, "a"); // In map

	hashMapDelete(map);

	printf("made it to end\n");


	return 0;
}