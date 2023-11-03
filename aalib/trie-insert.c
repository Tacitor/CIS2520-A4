#include <stdio.h>
#include <string.h> // for strcmp()
#include <ctype.h> // for isprint()
#include <stdlib.h> // for malloc()
#include <assert.h>

#include "trie_defs.h"



/** compare a key with the letter in a node */
int
trie_subtreeSearchComparator(const void *keyValue, const void *nodePtr)
{
	TrieNode **node = (TrieNode **) nodePtr;

	AAKeyType key = (AAKeyType) keyValue;
	return (key[0] - (*node)->letter);
}


/** create a whole chain for the rest of the key */
static TrieNode *
trie_create_chain(AAKeyType key, size_t keylength, void *value, int *cost)
{
	TrieNode *current = NULL;

	// TO DO: create a new chain the the required key letters

	return current;
}

/** add the given chain to the list of tries in the current node */
static int
trie_add_chain(
		TrieNode **subtreeList, int nSubtries,
		AAKeyType key,
		TrieNode *newChain
	)
{
	// TO DO:  add the provided chain to the node; the first letter
	// of the key may be used to organize where within the set of
	// subtries you add this

	// TO DO: you probably want to replace this return statement
	// with your own code
	return -1;
}


/** link the provided key into the current chain */
static int
trie_link_to_chain(TrieNode *current,
		AAKeyType key, size_t keylength,
		void *value, int *cost)
{
	// TO DO: add the remaining portions of the key
	// into this chain, forming a new branch if and when
	// they stop matching existing letters within the subtries

	// TO DO: you probably want to replace this return statement
	// with your own code
	return -1;
}


int
trieInsertKey(KeyValueTrie *root,
		AAKeyType key, size_t keylength,
		void *value, int *cost)
{
	/** keep the max key length in order to keep a buffer for interation */
	if (root->maxKeyLength < keylength)
		root->maxKeyLength = keylength;

	if (root->nSubtries == 0) {
		root->subtries[root->nSubtries++] = trie_create_chain(
				key, keylength, value, cost);
		return 0;
	}

	
	// TO DO: find the subtrie with the leading letter of the
	// key, and insert the new key into the correct subtrie
	// chain based on that letter

	// TO DO: you probably want to replace this return statement
	// with your own code
	return -1;
}


