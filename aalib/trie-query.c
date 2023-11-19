#include <stdio.h>
#include <string.h> // for strcmp()
#include <ctype.h> // for isprint()
#include <stdlib.h> // for malloc()
#include <assert.h>

#include "trie_defs.h"

/** recursive iterator helper function for lookup */
static void * trie_lookup_helper(TrieNode *node, AAKeyType key, size_t keyStartPos, size_t keylength, int ittoratorLen, int *cost)
{
	//check to see if the passed node is a match for the end of the key
	if (ittoratorLen == keylength)
	{
		//now check for a value at this location
		if (node->isKeySoHasValue)
		{
			return node->value;
		}
	}

	// check to see if this node has the required letter
	TrieNode *chain = trie_search_for_matching_chain(node->subtries, node->nSubtries, key[keyStartPos], cost);

	// check to see if we found a matching chain that already exists
	if (chain != NULL)
	{
		return trie_lookup_helper(chain, key, ++keyStartPos, keylength, ++ittoratorLen, cost);
	}
	else
	{
		/** return null if the node doesn't have a value */
		return NULL;
	}
	
}

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

	int ittoratorLen = 0;

	// check to see if this node has the required letter
	TrieNode *chain = trie_search_for_matching_chain(root->subtries, root->nSubtries, key[0], cost);

	// check to see if we found a matching chain that already exists
	if (chain != NULL)
	{
		return trie_lookup_helper(chain, key, 1, keylength, ++ittoratorLen, cost);
	}
	else
	{
		/** return null if the node doesn't have a value */
		return NULL;
	}
}

