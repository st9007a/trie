#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "trie.h"

#define BLOCK_SIZE (256 * sizeof(void*))
#define GET_CHILDREN(node) ((TrieNode**)((node)->payload & (0xffffffffffffffff << 2)))
#define IS_END(node) ((node)->payload & 0x01)
#define NEED_FREE(node) ((node)->payload & 0x10)


struct TrieNode {
    unsigned long payload;
};


static TrieNode* trie_init_with_pool(void* pool, size_t pool_size) {
    TrieNode* node;

    if (pool_size > 0 && pool) {
        node = pool;
        memset(pool, 0, BLOCK_SIZE);
        node->payload = (unsigned long)(pool + sizeof(TrieNode));
    } else {
        node = trie_init();
    }

    return node;
}

static inline void trie_add_with_pool(TrieNode* root, char* prefix, size_t length, void* pool, size_t pool_size) {
    if (!length) {
        root->payload |= 1;
        return;
    }

    TrieNode* cur = GET_CHILDREN(root)[(*prefix) - 1];

    if (!cur) {
        if (!pool || !pool_size) {
            pool = malloc(BLOCK_SIZE * length);
            pool_size = length;
        }

        cur = trie_init_with_pool(pool, pool_size);

        GET_CHILDREN(root)[(*prefix) - 1] = cur;

        pool += BLOCK_SIZE;
        --pool_size;
    }

    trie_add_with_pool(cur, prefix + 1, length - 1, pool, pool_size);

}


size_t trie_struct_size() { return sizeof(TrieNode); }


TrieNode* trie_init() {
    TrieNode* node = malloc(BLOCK_SIZE);
    memset(node, 0, BLOCK_SIZE);
    node->payload = (unsigned long)(node + 1) | 0x10;

    return node;
}

void trie_add(TrieNode* root, char* prefix, size_t length) {
    trie_add_with_pool(root, prefix, length, NULL, 0);
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
    printf("Enter node:\n");
    for (int i = 0; i < 255; ++i) {
        if (GET_CHILDREN(node)[i]) {
            printf("Access %c\n", i);
            trie_free(GET_CHILDREN(node)[i]);
        }
    }
    if (NEED_FREE(node)) {
        printf("Free\n");
        free(node);
    }
}
