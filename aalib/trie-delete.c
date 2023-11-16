#include <stdio.h>
#include <string.h> // for strcmp()
#include <ctype.h> // for isprint()
#include <stdlib.h> // for malloc()
#include <assert.h>

#include "trie_defs.h"


/** recursively roll up the chain */
/**
 * NOTE: This functions IS explained in the lecture slides
 */
static int
walk_chain_to_delete(
		void **value,
		TrieNode *curSearchNode,
		AAKeyType key, size_t keylength,
		int *cost
	)
{
	// TO DO: remove nodes for deleted key
	return 0;
}

/** delete a key from the trie */
/**
 * NOTE: This functions IS explained in the lecture slides
 */
void *trieDeleteKey(
		KeyValueTrie *root,
		AAKeyType key, size_t keylength,
		int *cost
	)
{
	void *valueFromDeletedKey = NULL;


	if (root->nSubtries == 0) {
		return NULL;
	}

	/**
	 ** TO DO: search for the right subchain and delete the key from it
	 **/

	//THIS IS NOT THE RIST CALL, I JUST WANT TO STOP SEEING WARNINGS
	walk_chain_to_delete(NULL, NULL, 0, 0, NULL);
	
	return valueFromDeletedKey;
}

