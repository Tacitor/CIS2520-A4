
# Associative arrays implemented using tries

## Name: Lukas Krampitz
## ID: 1192170

This `README.md` file describes an implementation of associative
arrays using *tries*, and evaluates when these are superior to
the use of a *hash table* based implementation.

# External resources used:

* Used binary search code from Lecture Slides 050-01-Searching-Pt2-handout-1.pdf
* Adapted pseudo code from Lecture Slides 070-01-Maps-Tries-handout.pdf

# State of the current implementation

Complete

# Hash tables:

## Strengths:

* Marginally faster when inserting from data-sets with few numbers of keys. Still within the same order of magnitude though.
* Marginally faster when deleting from data-sets with few numbers of keys. Still within the same order of magnitude though.
* Marginally faster when querying from data-sets with few numbers of keys. Still within the same order of magnitude though.
* Better performance with smaller data sets. Though this can vary with different hashing and probing algorithms

## Weaknesses

* Significantly slower when inserting from data-sets with many keys (5000+). Slower by at least 1 order of magnitude.
* Significantly slower when deleting from data-sets with many keys (5000+). Slower by at least 1 order of magnitude.
* Significantly slower when querying from data-sets with many keys (5000+). Slower by at least 1 order of magnitude.

# Tries:

## Strengths:

* Significantly faster when inserting from data-sets with many keys (5000+). Faster by at least 1 order of magnitude.
* Significantly faster when deleting from data-sets with many keys (5000+). Faster by at least 1 order of magnitude.
* Significantly faster when querying from data-sets with many keys (5000+). Faster by at least 1 order of magnitude.
* Better performance with shorter keys since less nodes need to be traversed to reach the value.

## Weaknesses

* Marginally slower when inserting from data-sets with few numbers of keys. Still within the same order of magnitude though.
* Marginally slower when deleting from data-sets with few numbers of keys. Still within the same order of magnitude though.
* Marginally slower when querying from data-sets with few numbers of keys. Still within the same order of magnitude though.

# Summary

## Conditions that would make a hash table appropriate:

Choose a hash table when *ALL* of the conditions in the **required**
list are true and any of the conditions in the **preferred** list
are true.

### Hash table **required** conditions
* One is using key/value paired data.
* If one has a large data-set a large block of memory need be able to be allocated.

### Hash table **preferred** conditions
* Few deletions will be made
* Queries mostly made for keys that are actually stored in the table


## Conditions that would make a trie appropriate:

Choose a trie when *ALL* of the conditions in the **required**
list are true and any of the conditions in the **preferred** list
are true.

### Trie **required** conditions
* One is using key/value paired data
* All keys are string-based or can be treated as strings without issues
* Data can be stored in lexicographic ordering

### Trie **preferred** conditions
* Keys are short


