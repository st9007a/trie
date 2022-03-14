#include <stdlib.h>
#include <stdio.h>

#include "trie.h"

struct TrieNode {
    char ch;
    size_t n;
    size_t s;
    struct TrieNode** children;
    unsigned char end;
};


size_t trie_struct_size() { return sizeof(TrieNode); }


TrieNode* trie_init() {
    TrieNode* root = malloc(sizeof(TrieNode));
    root->ch = '\0';
    root->n = 0;
    root->s = 0;
    root->children = NULL;
    root->end = 0;

    return root;
}


void trie_add(TrieNode* root, char* prefix, size_t length) {
    if (length == 0) {
        root->end = 1;
        return;
    }

    TrieNode* cur = NULL;

    for (int i = 0; i < root->n; ++i) {
        if (root->children[i]->ch == prefix[0]) {
            cur = root->children[i];
            break;
        }
    }

    if (cur) {
        trie_add(cur, prefix + 1, length - 1);
    } else {
        TrieNode* node = trie_init();
        node->ch = prefix[0];

        if (root->s == 0) {
            root->children = malloc(sizeof(TrieNode*));
            root->s = 1;
        } else if (root->s < root->n + 1) {
            root->children = realloc(root->children, sizeof(TrieNode*) * 2 * root->s);
            root->s *= 2;
        }

        root->children[root->n] = node;
        root->n += 1;

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

    TrieNode* cur = NULL;

    for (int i = 0; i < root->n; ++i) {
        if (root->children[i]->ch == query[0]) {
            cur = root->children[i];
            break;
        }
    }

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

    for (int i = 0; i < node->n; ++i) {
        trie_free(node->children[i]);
    }

    if (node->children) {
        free(node->children);
    }
    free(node);
}
