# Trie

工作的時候跟同事討論到一個需要用trie來解決的問題, 所以非常無聊得用C語言實作了一下,
由於總共實作了三個版本, 每個版本都有其優化, 覺得滿有趣的, 故記錄一下

## 免責聲明

目前這三個版本的實作都是以記憶體足夠大且執行在64位元機器的前提下設計的, 因此不保證在所有平台都可以正常運作,
也不保證執行效率是最好的

## Introduction

A simple C implementation of trie which supports inserting string patterns and matching prefix.
Note that the structure to index children is hash table which will make it memory-unfriendly
but gurantee the time complexity of indexing is `O(1)`.
The current implementation doesn't support deleting a string pattern.

## Project Structure

- `trie.h`: Define the interface of trie.
- `trie_v1.c`: Use a dynamic array to store children.
- `trie_v2.c`: Use a hash table to store children.
- `trie_opt.c`: Optimize `trie_v2` with cache-friendly designing.
    - Use a hash table to store children.
    - Replace recursive calls with a loop in `trie_search`.
    - Ensure allocated memory as contingous as possible.
    - Align allocated size of memory pool to 2048 which divides L1 cache size without remainder.
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

And you will see the output:
```
sizeof(TrieNode): 40 bytes
Search time: 0.602957 seconds
sizeof(TrieNode): 16 bytes
Search time: 0.519955 seconds
sizeof(TrieNode): 8 bytes
Search time: 0.504131 seconds
```

`trie_v1` is very slow in searching and a trie node is larger than other two implementations.
`trie_opt` is the smallest and slightly faster than `trie_v2`.
