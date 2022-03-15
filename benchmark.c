#include <stdio.h>
#include <string.h>
#include <time.h>

#include "trie.h"

int main() {

    char line[1024];
    TrieNode* root;
    clock_t begin, end;

    double total = 0.;
    FILE *prefix = fopen("prefix.txt", "r");
    FILE *query = fopen("query.txt", "r");

    if (!prefix) {
        printf("prefix.txt doesn't exist.");
        return 1;
    }

    if (!query) {
        printf("query.txt doesn't exist.");
        return 1;
    }

    root = trie_init();

    while(fgets(line, sizeof(line), prefix) != NULL) {
        trie_add(root, line, strlen(line) - 1);
    }

    fclose(prefix);

    printf("sizeof(TrieNode): %ld bytes\n", trie_struct_size());

    while(fgets(line, sizeof(line), query) != NULL) {
        begin = clock();
        trie_search(root, line, strlen(line));
        end = clock();
        total += (double)(end - begin);
    }

    printf("Search time: %lf seconds\n", total / 1e6);

    fclose(query);
    trie_free(root);

    return 0;
}
