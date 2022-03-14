# Trie

工作的時候跟同事討論到一個需要用trie來解決的問題, 所以非常無聊得用C語言實作了一下,
由於總共實作了三個版本, 每個版本都有其優化, 覺得滿有趣的, 故記錄一下

A simple C implementation of trie which supports inserting string patterns and matching prefix.
Note that the structure to index children is hash table which will make it memory unfriendly
but gurantee the time complexity of indexing is `O(1)`.
The current implementation doesn't support delete a string pattern.

## Project Structure

- `trie.h`: Define the interface of trie.
- `trie_v1.c`: Use a dynamic array to store children.
- `trie_v2.c`: Use a hash table to store children.
- `trie_opt.c`: Optimize `trie_v2` with cache-friendly designing.
    - Use a hash table to store children.
    - Ensure allocated memory as contingous as possible.
    - Minimize size of trie node structure.
- `test.c`: Test result of trie.
- `benchmark.c`: Check trie size and executing time.

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
