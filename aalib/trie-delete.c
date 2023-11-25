#include <stdio.h>
#include <string.h> // for strcmp()
#include <ctype.h> // for isprint()
#include <stdlib.h> // for malloc()
#include <assert.h>

#include "trie_defs.h"

/**
 * Given a list of subtries remove one of them from the list
 *
 * NOTE: This functions is NOT explained in the lecture slides
 */
static int trie_detatch_chain(TrieNode ***subTrieListPTR, int nSubtries, TrieNode *childNode)
{
	TrieLetter keyLetter = childNode->letter;

	//find the removal index
	int removalIndex = trie_search_for_matching_index((*subTrieListPTR), nSubtries, keyLetter, 0);

	nSubtries--;
	TrieNode ** newList = malloc(sizeof(TrieNode *) * (nSubtries));

	//transfer over all other values
	for (int i = 0; i < (nSubtries); i++) 
	{
		if (i < removalIndex) {
			newList[i] = (*subTrieListPTR)[i];
		} else {
			newList[i] = (*subTrieListPTR)[i + 1];
		}
	}

	//free the child node that is no longer needed
	free(childNode->subtries); //assume this line is safe because this function only every gets called when a childNode has no children
	free(childNode); //plus we are getting ride of the whole node anyway so it better be not having any children

	//free the old table
	free((*subTrieListPTR));
	//reassign it to the new table
	(*subTrieListPTR) = newList;

	return nSubtries;
}

/** recursively roll up the chain */
/**
 * NOTE: This functions IS explained in the lecture slides
 */
static int
walk_chain_to_delete(
		void **value,
		TrieNode *curSearchNode,
		AAKeyType key, size_t keyStartPos, size_t keylength,
		int *cost
	)
{
	// DONE: remove nodes for deleted key

	if (keylength - keyStartPos == 1)
	{
		if (curSearchNode->isKeySoHasValue)
		{
			curSearchNode->isKeySoHasValue = 0;
			(*value) = curSearchNode->value;
			curSearchNode->value = NULL;

			if (curSearchNode->nSubtries == 0)
			{
				return 1; // roll up this chain
			}
		}

		return 0; // we are done, but don’t roll up this chain
	}

	// Search for the next letter of the key
	keyStartPos++;
	TrieNode *child = trie_search_for_matching_chain(curSearchNode->subtries, curSearchNode->nSubtries, key[keyStartPos], cost);

	if (child == NULL)
	{
		return 0; // no match
	}

	// recursively walk the rest of the chain
	if (walk_chain_to_delete(value, child, key, keyStartPos, keylength, cost))
	{
		// remove our child
		curSearchNode->nSubtries = trie_detatch_chain(&(curSearchNode->subtries), curSearchNode->nSubtries, child);

		//if we have no children left and no value, keep rolling up
		if (!curSearchNode->isKeySoHasValue && curSearchNode->nSubtries == 0)
		{
			return 1;
		}
	}

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
	 ** DONE: search for the right subchain and delete the key from it
	 **/

	//Search for the first letter of the key
	TrieNode *chain = trie_search_for_matching_chain(root->subtries, root->nSubtries, key[0], cost);

	if (chain == NULL) {
		return NULL; // no match
	}

	int fullyCompletely = walk_chain_to_delete(&valueFromDeletedKey, chain, key, 0, keylength, cost);

	//if fully deleted, remove this entry from the set of subtries
	if (fullyCompletely)
	{
		root->nSubtries = trie_detatch_chain(&(root->subtries), root->nSubtries, chain);
	}
	
	return valueFromDeletedKey;
}

