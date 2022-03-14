#ifdef TRIE_OPT
#include <stdlib.h>

#include "trie.h"

#define GET_CHILDREN(node) ((TrieNode**)((node)->payload & (0xffffffffffffffff << 2)))
#define IS_END(node) ((node)->payload & 0x1)
#define NEED_FREE(node) ((node)->payload & 0x10)


struct TrieNode {
    unsigned long payload;
};


size_t trie_struct_size() { return sizeof(TrieNode); }


TrieNode* trie_init(TrieNode* pool, size_t pool_size) {
    TrieNode* node;
    unsigned char need_free;

    if (pool_size > 0 && pool) {
        node = pool;
        need_free = 0;
    } else {
        node = malloc(sizeof(TrieNode));
        need_free = 2;
    }

    node->payload = (unsigned long)calloc(256, sizeof(TrieNode*));
    node->payload |= need_free;

    return node;
}

void trie_add(TrieNode* root, char* prefix, size_t length, TrieNode* pool, size_t pool_size) {
    if (length == 0) {
        root->payload |= 1;
        return;
    }

    TrieNode* cur = GET_CHILDREN(root)[*prefix];

    if (cur) {
        trie_add(cur, prefix + 1, length - 1, pool, pool_size);
    } else {
        if (!pool) {
            pool = malloc(sizeof(TrieNode) * length);
            pool_size = length;
        }

        TrieNode* node = trie_init(pool, pool_size);

        GET_CHILDREN(root)[*prefix] = node;
        trie_add(node, prefix + 1, length - 1, pool + 1, pool_size - 1);
    }
}


int trie_search(TrieNode* root, char* query, size_t length) {
    while (length && !IS_END(root)) {
        root = GET_CHILDREN(root)[*query];
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
    for (int i = 0; i < 256; ++i) {
        if (GET_CHILDREN(node)[i]) {
            trie_free(GET_CHILDREN(node)[i]);
        }
    }
    free(GET_CHILDREN(node));
    if (NEED_FREE(node)) {
        free(node);
    }
}

#endif
