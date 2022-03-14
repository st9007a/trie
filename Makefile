CFLAGS = -Wall
EXEC = trie_v1 trie_v2 trie_opt
TEST = trie_v1_test trie_v2_test trie_opt_test

MAIN = benchmark.c
TEST_MAIN = test.c

.PHONY: all clean

all: $(EXEC) $(TEST)


run: $(EXEC)
	@for exec in $(EXEC); do \
		./$$exec; \
	done

test: $(TEST)
	@for exec in $(TEST); do \
		./$$exec; \
	done

trie_v1: trie_v1.c trie.h
	gcc $< $(MAIN) -o $@ $(CFLAGS)

trie_v2: trie_v2.c trie.h
	gcc $< $(MAIN) -o $@ $(CFLAGS)

trie_opt: trie_opt.c trie.h
	gcc $< $(MAIN) -o $@ -DTRIE_OPT $(CFLAGS)

trie_v1_test: trie_v1.c trie.h
	gcc $< $(TEST_MAIN) -o $@ $(CFLAGS)

trie_v2_test: trie_v2.c trie.h
	gcc $< $(TEST_MAIN) -o $@ $(CFLAGS)

trie_opt_test: trie_opt.c trie.h
	gcc $< $(TEST_MAIN) -o $@ -DTRIE_OPT $(CFLAGS)

clean:
	rm -rf $(EXEC) $(TEST)
