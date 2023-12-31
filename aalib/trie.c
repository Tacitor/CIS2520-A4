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
	free(node->subtries);
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
	free(trie->subtries);
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
 *
 */
int trie_search_for_matching_index(struct TrieNode **subtries, int nSubtries, TrieLetter letter, int returnNonFail)
{
	int left = 0;
	int right = nSubtries - 1;
	int middle = 0;

	// loop until search range collapses
	while (left <= right)
	{
		// calculate half way, round down
		middle = (int)((left + right) / 2);

		if ((int)subtries[middle]->letter < (int)letter)
		{ // too low
			left = middle + 1;
		}
		else if ((int)subtries[middle]->letter > (int)letter)
		{ // too hight
			right = middle - 1;
		}
		else
		{
			return middle;
		}
	}

	// always return the location an index SHOULD be even if it is not there
	if (returnNonFail && (int)subtries[middle]->letter < (int)letter)
	{
		return middle + 1;
	}
	else if (returnNonFail)
	{
		return middle;
	}
	else
	{
		return -1;
	}
}

/**
 * Given a list of nodes find the node that matches the given letter.
 *
 * @return may return NULL if no match. Otherwise return the TrieNode* that points to the node with the matching letter
 */
TrieNode *trie_search_for_matching_chain(struct TrieNode **subtries, int nSubtries, TrieLetter letter, int *cost)
{

	int index = trie_search_for_matching_index(subtries, nSubtries, letter, 0);

	if (index != -1 && trie_subtreeSearchComparator(&letter, &(subtries[index])) == 0)
	{

		// if the cost pointer isn't null then increment it by 1 to account for traversing this 1 part of the chain
		if (cost != NULL)
		{
			(*cost)++;
		}

		return subtries[index];
	}

	// return null if no match
	return NULL;
}

