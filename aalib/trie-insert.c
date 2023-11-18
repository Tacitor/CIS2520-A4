#include <stdio.h>
#include <string.h> // for strcmp()
#include <ctype.h> // for isprint()
#include <stdlib.h> // for malloc()
#include <assert.h>

#include "trie_defs.h"

static int trie_add_chain(TrieNode ***, int, AAKeyType, TrieNode *);

/** compare a key with the letter in a node */
int
trie_subtreeSearchComparator(const void *keyValue, const void *nodePtr)
{
	TrieNode **node = (TrieNode **) nodePtr;

	AAKeyType key = (AAKeyType) keyValue;
	return (key[0] - (*node)->letter);
}


/** create a whole chain for the rest of the key */
/**
 * NOTE: This functions IS explained in the lecture slides
 */
static TrieNode *
trie_create_chain(AAKeyType key, int keyStartPos , size_t keylength, void *value, int *cost)
{
	TrieNode *current = NULL;

	// DONE: create a new chain the the required key letters

	// DONE: do something with this cost variable
	// if the cost pointer isn't null then the local cost can be added on
	if (cost != NULL)
	{
		(*cost)++;
	}

	current = trieCreateNode();

	current->letter = (TrieLetter)key[keyStartPos];

	if (keylength - keyStartPos == 1)
	{
		current->value = value;
		current->isKeySoHasValue = 1; //set this to being a valid key

		//debug insertion with linking to existing chains
		//printf("DONE: %s, with : %ld\n", key, keylength - keyStartPos);
	}
	else
	{
		keyStartPos++;
		// recurse
		current->nSubtries = trie_add_chain(&(current->subtries), current->nSubtries, &(key[keyStartPos]), trie_create_chain(key, keyStartPos, keylength, value, cost));
	}

	return current;
}

/** add the given chain to the list of tries in the current node */
/**
 * NOTE: This functions is NOT explained in the lecture slides
 */
static int
trie_add_chain(
		TrieNode ***subtreeListPTR, int nSubtries,
		AAKeyType key,
		TrieNode *newChain
	)
{
	// DONE: add the provided chain to the node; the first letter
	// of the key may be used to organize where within the set of
	// subtries you add this

	// first check if this is a new subtrie
	if ((*subtreeListPTR) == NULL)
	{
		(*subtreeListPTR) = malloc(sizeof(TrieNode*));
		//count this as the first subtrie
		nSubtries = 1;

	}
	else
	{
		// first increase the size of the subtree list
		// also increment nSubtries by 1 to account for the larger size now
		(*subtreeListPTR) = realloc((*subtreeListPTR), (sizeof(TrieNode *) * (++nSubtries)));
	}

	/**
	 * TO DO: Use a Binary Search to add this in
	 * Assume the subtreeList is already sorted because all the others chains will have been added this way
	 */
	// just append it for now cause that's easier
	(*subtreeListPTR)[nSubtries - 1] = newChain;

	// DONE: you probably want to replace this return statement
	// with your own code
	return nSubtries;
}


/** link the provided key into the current chain */
/**
 * NOTE: This functions IS explained in the lecture slides
 */
static int
trie_link_to_chain(TrieNode *current,
		AAKeyType key, int keyStartPos, size_t keylength,
		void *value, int *cost)
{
	// DONE: add the remaining portions of the key
	// into this chain, forming a new branch if and when
	// they stop matching existing letters within the subtries

	TrieNode *child = trie_search_for_matching_chain(current->subtries, current->nSubtries, key[keyStartPos + 1], cost);

	//debug insertion with linking to existing chains
	//printf("Key: %s, currentStartPOs: %c, len-start: %ld, Child is NULL: %d\n", key, key[keyStartPos], keylength - keyStartPos, child == NULL);

	// Either there was no result found or
	// key[keyStartPos + 1] is the null terminator of the string
	if (child == NULL || (keylength - keyStartPos - 1 == 1))
	{
		// add the remaining letters as a side chain
		current->nSubtries = trie_add_chain(&(current->subtries), current->nSubtries, &(key[keyStartPos + 1]), trie_create_chain(key, keyStartPos + 1, keylength, value, cost));

		return current->nSubtries;
	}
	else
	{
		// recurse
		return trie_link_to_chain(child, key, keyStartPos + 1, keylength, value, cost);
	}

	// DONE: you probably want to replace this return statement
	// with your own code
	return -1;
}


/**
 * NOTE: This functions IS explained in the lecture slides
 */
int
trieInsertKey(KeyValueTrie *root,
		AAKeyType key, size_t keylength,
		void *value, int *cost)
{
	// DONE: do something with this cost variable

	/** keep the max key length in order to keep a buffer for interation */
	if (root->maxKeyLength < keylength)
		root->maxKeyLength = keylength;

	if (root->nSubtries == 0) {
		// if this is 0 then there is no table yet
		// first allocate the table
		// start it at size 1 becasue that way the nSubtries variable will always be able to tell us how many nodes are direct children
		// this is decided to be the best option because I believe we were told not to modify the API so I cannot add a new varible that
		// keeps track of the size of the array seperate from nSubtries.
		root->subtries = (TrieNode **)malloc(sizeof(TrieNode *)); // give it a size of 1 to start

		root->subtries[root->nSubtries++] = trie_create_chain(
				key, 0, keylength, value, cost);
		return 0;
	}
	else // If the trie is not empty and there are already existing chains
	{
		// DONE: find the subtrie with the leading letter of the
		// key, and insert the new key into the correct subtrie
		// chain based on that letter

		TrieNode *chain = trie_search_for_matching_chain(root->subtries, root->nSubtries, key[0], cost);

		// check to see if we found a matching chain that already exists
		if (chain == NULL)
		{
			// add the new chain to the table of subtries
			root->nSubtries = trie_add_chain(&(root->subtries), root->nSubtries, key, trie_create_chain(key, 0, keylength, value, cost));

			return root->nSubtries;
		}
		else
		{
			return trie_link_to_chain(chain, key, 0, keylength, value, cost);
		}
	}

	// DONE: you probably want to replace this return statement
	// with your own code
	return -1;
}


