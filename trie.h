#ifndef TRIE_H
#define TRIE_H

#include <stdlib.h>

struct TrieNode;

typedef struct TrieNode TrieNode;

TrieNode* trie_init();

void trie_add(TrieNode*, char*, size_t);

size_t trie_struct_size();

int trie_search(TrieNode*, char*, size_t);

void trie_free(TrieNode*);

#endif
