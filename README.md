# Trie

A simple C implementation of  trie.
The structure to index children is hash table which will make it memory unfriendly
but gurantee the time complexity of indexing is `O(1)`.

## Project Structure

- `trie.h`: Define the interface of trie.
- `trie_v1.c`: Use a dynamic array to store children.
- `trie_v2.c`: Use a hash table to store children.
- `trie_opt.c`: Optimize `trie_v2` with cache-friendly designing.
    - Use a hash table to store children.
    - Ensure allocated memory as contingous as possible.
    - Minimize size of trie node structure.

## Simple Testing

```
$ make test
```

## Benchmarking

1. Generate test data

```
$ python3 gen_test_data.py
```

2. Run benchmark

```
$ make run
```
