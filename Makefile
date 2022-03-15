CFLAGS = -Wall

PREFIX = trie_v1 trie_v2 trie_opt

BENCHMARK := $(addsuffix _benchmark, $(PREFIX))
TEST := $(addsuffix _test, $(PREFIX))

.PHONY: all clean run

all: $(BENCHMARK) $(TEST)


run: $(BENCHMARK)
	@for exec in $(BENCHMARK); do \
		./$$exec; \
	done

test: $(TEST)
	@for exec in $(TEST); do \
		./$$exec; \
	done

%_benchmark: %.c trie.h
	gcc $< benchmark.c -o $@ $(CFLAGS)

%_test: %.c trie.h
	gcc $< test.c -o $@ $(CFLAGS)

clean:
	rm -rf $(BENCHMARK) $(TEST)
