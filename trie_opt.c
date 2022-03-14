#ifdef TRIE_OPT
#include <stdlib.h>
#include <string.h>

#include "trie.h"

#define GET_CHILDREN(node) ((TrieNode**)((node)->payload & (0xffffffffffffffff << 2)))
#define IS_END(node) ((node)->payload & 0x1)
#define NEED_FREE(node) ((node)->payload & 0x10)


struct TrieNode {
    unsigned long payload;
};


size_t trie_struct_size() { return sizeof(TrieNode); }


TrieNode* trie_init(void* pool, size_t pool_size) {
    TrieNode* node;
    unsigned char need_free;

    if (pool_size > 0 && pool) {
        node = pool;
        memset(pool + sizeof(TrieNode), 0, 255 * sizeof(TrieNode*));
        node->payload = (unsigned long)(pool + sizeof(TrieNode));
        need_free = 0;
    } else {
        node = malloc(sizeof(TrieNode));
        node->payload = (unsigned long)calloc(255, sizeof(TrieNode*));
        need_free = 2;
    }

    node->payload |= need_free;

    return node;
}

void trie_add(TrieNode* root, char* prefix, size_t length, void* pool, size_t pool_size) {
    if (!length) {
        root->payload |= 1;
        return;
    }

    TrieNode* cur = GET_CHILDREN(root)[(*prefix) - 1];

    if (!cur) {
        if (!pool || !pool_size) {
            pool = malloc(sizeof(void*) * length * 256);
            pool_size = length;
        }

        cur = trie_init(pool, pool_size);

        GET_CHILDREN(root)[(*prefix) - 1] = cur;

        pool += sizeof(TrieNode) + 255 * sizeof(TrieNode*);
        --pool_size;
    }

    trie_add(cur, prefix + 1, length - 1, pool, pool_size);
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

#endif
