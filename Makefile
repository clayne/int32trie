CC      = cc
CFLAGS  = -O3 -Wall -Wextra -Wno-int-in-bool-context
LDFLAGS = -fsanitize=address -fsanitize=undefined
LDLIBS  =

check: test
	./test

test: test.c uint32trie.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ test.c uint32trie.c $(LDLIBS)
