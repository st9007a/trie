#include <assert.h>
#include <string.h>
#include "trie.h"

int main() {

    TrieNode* root;

    char* prefix[4];

    prefix[0] = "abc";
    prefix[1] = "abde";
    prefix[2] = "cgh";
    prefix[3] = "bbbbb";

    root = trie_init();

    // for (int i = 0; i < 4; ++i) {
    //     trie_add(root, prefix[i], strlen(prefix[i]));
    // }

    // assert(trie_search(root, "abced", 5) == 1);
    // assert(trie_search(root, "ab", 2) == 0);
    // assert(trie_search(root, "bbbb", 4) == 0);
    // assert(trie_search(root, "abdehji", 7) == 1);
    // assert(trie_search(root, "bbbbbbbbbb", 10) == 1);

    trie_free(root);

    return 0;
}
