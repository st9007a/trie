#include <stdlib.h>
#include <stdio.h>

#include "trie.h"

struct TrieNode {
    struct TrieNode** children;
    unsigned char end;
};


size_t trie_struct_size() { return sizeof(TrieNode); }


TrieNode* trie_init() {
    TrieNode* root = malloc(sizeof(TrieNode));
    root->children = calloc(256, sizeof(TrieNode*));
    root->end = 0;

    return root;
}


void trie_add(TrieNode* root, char* prefix, size_t length) {
    if (length == 0) {
        root->end = 1;
        return;
    }

    TrieNode* cur = root->children[prefix[0]];

    if (cur) {
        trie_add(cur, prefix + 1, length - 1);
    } else {
        TrieNode* node = trie_init();

        root->children[prefix[0]] = node;
        trie_add(node, prefix + 1, length - 1);
    }
}


int trie_search(TrieNode* root, char* query, size_t length) {
    if (root->end) {
        return 1;
    }

    if (length == 0) {
        return root->end;
    }

    TrieNode* cur = root->children[query[0]];

    if (cur) {
        return trie_search(cur, query + 1, length - 1);
    } else {
        return 0;
    }
}

void trie_free(TrieNode* node) {
    if (!node) {
        return;
    }
    for (int i = 0; i < 256; ++i) {
        if (node->children[i]) {
            trie_free(node->children[i]);
        }
    }
    free(node->children);
    free(node);
}
