#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "trie.h"

#define BLOCK_SIZE (256 * sizeof(void*))
#define GET_CHILDREN(node) ((TrieNode**)((node)->payload & (0xffffffffffffffff << 2)))
#define IS_END(node) ((node)->payload & 1)
#define NEED_FREE(node) ((node)->payload & 2)


struct TrieNode {
    unsigned long payload;
};


static inline void trie_add_with_pool(TrieNode* root, char* prefix, size_t length, void* pool) {
    if (!length) {
        root->payload |= 1;
        return;
    }

    TrieNode* cur = GET_CHILDREN(root)[(*prefix) - 1];

    if (!cur) {
        if (!pool) {
            pool = malloc(BLOCK_SIZE * length);
        }

        memset(pool, 0, BLOCK_SIZE);
        cur = pool;
        cur->payload = (unsigned long)(pool + sizeof(TrieNode));

        GET_CHILDREN(root)[(*prefix) - 1] = cur;

        pool += BLOCK_SIZE;
    }

    trie_add_with_pool(cur, prefix + 1, length - 1, pool);

}


size_t trie_struct_size() { return sizeof(TrieNode); }


TrieNode* trie_init() {
    TrieNode* node = malloc(BLOCK_SIZE);
    memset(node, 0, BLOCK_SIZE);
    node->payload = (unsigned long)(node + 1) | 2;

    return node;
}

void trie_add(TrieNode* root, char* prefix, size_t length) {
    trie_add_with_pool(root, prefix, length, NULL);
}


int trie_search(TrieNode* root, char* query, size_t length) {
    while (length && !IS_END(root)) {
        root = GET_CHILDREN(root)[(*query) - 1];
        if (root) {
            ++query;
            --length;
        } else {
            return 0;
        }
    }

    return IS_END(root);
}

void trie_free(TrieNode* node) {
    if (!node) {
        return;
    }
    for (int i = 0; i < 255; ++i) {
        if (GET_CHILDREN(node)[i]) {
            trie_free(GET_CHILDREN(node)[i]);
        }
    }
    if (NEED_FREE(node)) {
        free(node);
    }
}
