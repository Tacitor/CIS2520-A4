#include <stdio.h>
#include <string.h> // for strcmp()
#include <ctype.h> // for isprint()
#include <stdlib.h> // for malloc()
#include <assert.h>

#include "trie_defs.h"


/** create the overall trie */
KeyValueTrie *
trieCreateTrie()
{
	KeyValueTrie *root;

	root = (KeyValueTrie *) malloc(sizeof(KeyValueTrie));

	/**
	 * DONE: Select Option 1
	 * 1) simply initialize "root->subtries" to NULL here (and get rid of the loop altogether) -- this will mean that you will want to create the table somewhere else before you attempt to insert values into it
	 * OR
	 * 2) create a table attached to root->subtries here before the loop begins.
	 */
	root->subtries = NULL;
	root->nSubtries = 0;
	root->maxKeyLength = 0;
	return root;
}

/** recursive iterator helper function for deletion */
static void
trie_delete_helper(TrieNode *node)
{
	int i;

	if (node == NULL)	return;

	for (i = 0 ; i < node->nSubtries; i++) {
		trie_delete_helper(node->subtries[i]);
	}
	free(node);
}

/** delete the entire trie and all keys */
void
trieDeleteTrie(KeyValueTrie *trie)
{
	int i;

	for (i = 0 ; i < trie->nSubtries; i++) {
		trie_delete_helper(trie->subtries[i]);
	}
	free(trie);
}

/** create and initialize an empty node */
TrieNode *
trieCreateNode()
{
	TrieNode *newNode = (TrieNode *) malloc(sizeof(TrieNode));
	memset(newNode, 0, sizeof(TrieNode));
	return newNode;
}

/** clean up a single node */
void
trieDeleteNode(TrieNode *node)
{
	free(node);
}

#define	INDENT	4

/** recursive helper for printing */
static void
trie_print_sub_trie(FILE *fp, TrieNode *node, int depth)
{
	int i;

	for (i = 0; i < depth; i++) {
		fprintf(fp, "%*s", INDENT, "");
	}

	if (isprint(node->letter))
		fprintf(fp, "[%c]%c", node->letter,
				node->isKeySoHasValue ? '+' : ' ');
	else
		fprintf(fp, "[0x%02x]%c", node->letter,
				node->isKeySoHasValue ? '+' : ' ');
	while (node->nSubtries == 1) {
		node = node->subtries[0];
		depth++;
		if (isprint(node->letter))
			fprintf(fp, "[%c]%c", node->letter,
					node->isKeySoHasValue ? '+' : ' ');
		else
			fprintf(fp, "[0x%02x]%c", node->letter,
					node->isKeySoHasValue ? '+' : ' ');
	}
	fprintf(fp, "\n");
	for (i = 0; i < node->nSubtries; i++) {
		trie_print_sub_trie(fp, node->subtries[i], depth+1);
	}
}


/* print out the trie nicely, sideways */
void
triePrint(FILE *fp, KeyValueTrie *root)
{
	int i;

	if (root->nSubtries == 0) {
		fprintf(fp, "This trie is empty!\n");
		return;
	}

	for (i = 0; i < root->nSubtries; i++) {
		fprintf(fp, "%03d:\n", i);
		trie_print_sub_trie(fp, root->subtries[i], 1);
	}
}


//=-=-= Custom Functions written by Lukas =-=-=

/**
 * Given a list of nodes find the node that matches the given letter.
 *
 * @return may return NULL if no match. Otherwise return the TrieNode* that points to the node with the matching letter
 */
TrieNode *trie_search_for_matching_chain(struct TrieNode **subtries, int nSubtries, TrieLetter letter, int *cost)
{

	// create a local lost varible
	int localCost = 0;

	// itterate over the list of nodes
	for (int i = 0; i < nSubtries; i++)
	{
		localCost++;

		if (trie_subtreeSearchComparator(&letter, &(subtries[i])) == 0)
		{

			// if the cost pointer isn't null then the local cost can be added on
			if (cost != NULL)
			{
				*cost += localCost;
			}

			return subtries[i];
		}
	}

	// if the cost pointer isn't null then the local cost can be added on
	if (cost != NULL)
	{
		*cost += localCost;
	}

	// return null if no match
	return NULL;
}

