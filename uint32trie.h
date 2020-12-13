#ifndef TRIE_H
#define TRIE_H

#include <stdint.h>

// Initialize to zero.
struct uint32trie {
    uint32_t len, cap;
    struct {
        uint32_t child[16];
        int value;
    } *nodes;
};

// Return the value for the given integer key, or 0 if not present.
int trie_get(const struct uint32trie *, int32_t);

// Set the stored boolean for the given integer, or 0 to remove.
// Returns 0 if out of memory.
int trie_put(struct uint32trie *t, int32_t x, int b);

// Free all of the trie's resources and reset to zero.
void trie_free(struct uint32trie *t);

#endif
