
# Associative arrays implemented using tries

## Name: Lukas Krampitz
## ID: 1192170

This `README.md` file describes an implementation of associative
arrays using *tries*, and evaluates when these are superior to
the use of a *hash table* based implementation.

# External resources used:

* Used binary search code from Lecure Slides 050-01-Searching-Pt2-handout-1.pdf
* Adapted psudo code from Lecure Slides 070-01-Maps-Tries-handout.pdf

# State of the current implementation

Complete

# Hash tables:

## Strengths:

* Marginally faster when inserting from data-sets with few numbers of keys. Still within the same order of magnitude though.
* Marginally faster when deleting from data-sets with few numbers of keys. Still within the same order of magnitude though.
* Marginally faster when quering from data-sets with few numbers of keys. Still within the same order of magnitude though.

## Weaknesses

* Significatly slower when inserting from data-sets with many keys (5000+). Slower by atleast 1 order of magnitude.
* Significatly slower when deleting from data-sets with many keys (5000+). Slower by atleast 1 order of magnitude.
* Significatly slower when quering from data-sets with many keys (5000+). Slower by atleast 1 order of magnitude.


# Tries:

## Strengths:

* Significatly faster when inserting from data-sets with many keys (5000+). Slower by atleast 1 order of magnitude.
* Significatly faster when deleting from data-sets with many keys (5000+). Slower by atleast 1 order of magnitude.
* Significatly faster when quering from data-sets with many keys (5000+). Slower by atleast 1 order of magnitude.

## Weaknesses

* Marginally slower when inserting from data-sets with few numbers of keys. Still within the same order of magnitude though.
* Marginally slower when deleting from data-sets with few numbers of keys. Still within the same order of magnitude though.
* Marginally slower when quering from data-sets with few numbers of keys. Still within the same order of magnitude though.


# Summary

## Conditions that would make a hash table appropriate:

Choose a hash table when *ALL* of the conditions in the **required**
list are true and any of the conditions in the **preferred** list
are true.

### Hash table **required** conditions
* condition
* condition

### Hash table **preferred** conditions
* condition
* condition



## Conditions that would make a trie appropriate:

Choose a trie when *ALL* of the conditions in the **required**
list are true and any of the conditions in the **preferred** list
are true.

### Trie **required** conditions
* condition
* condition

### Trie **preferred** conditions
* condition
* condition


