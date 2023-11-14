#include <stdio.h>
#include <string.h> // for strcmp()
#include <ctype.h> // for isprint()
#include <stdlib.h> // for malloc()
#include <assert.h>

#include "trie_defs.h"


/** find a key within the trie */
/**
 * NOTE: This functions is NOT explained in the lecture slides
 */
void *trieLookupKey(
		KeyValueTrie *root,
		AAKeyType key, size_t keylength,
		int *cost
	)
{
	// TO DO: walk the trie to find the key, returning
	// a value if there is one after we have finished
	// our walk

	/** return null if the node doesn't have a value */
	return NULL;
}

