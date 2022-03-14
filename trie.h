#ifndef TRIE_H
#define TRIE_H

#include <stdlib.h>

struct TrieNode;

typedef struct TrieNode TrieNode;

#ifdef TRIE_OPT
TrieNode* trie_init(TrieNode* pool, size_t pool_size);
void trie_add(TrieNode* root, char* prefix, size_t length, TrieNode* pool, size_t pool_size);
#else
TrieNode* trie_init();
void trie_add(TrieNode*, char*, size_t);
#endif

size_t trie_struct_size();

int trie_search(TrieNode*, char*, size_t);

void trie_free(TrieNode*);

#endif
