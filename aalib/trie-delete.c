#include <stdio.h>
#include <string.h> // for strcmp()
#include <ctype.h> // for isprint()
#include <stdlib.h> // for malloc()
#include <assert.h>

#include "trie_defs.h"


/** recursively roll up the chain */
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
	
	return valueFromDeletedKey;
}

