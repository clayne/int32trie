CC      = cc
CFLAGS  = -O3 -Wall -Wextra -Wno-int-in-bool-context
LDFLAGS = -fsanitize=address -fsanitize=undefined
LDLIBS  =

check: test
	./test

test: test.c int32trie.c int32trie.h
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ test.c int32trie.c $(LDLIBS)
