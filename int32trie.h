/* This is free and unencumbered software released into the public domain. */
#ifndef TRIE_H
#define TRIE_H

#include <stdint.h>

// Initialize to zero.
struct int32trie {
    uint32_t len, cap;
    union {
        uint32_t child[16];
        long value;
    } *nodes;
};

// Return the value for the given integer key, or 0 if not present.
long int32trie_get(const struct int32trie *, int32_t);

// Set the stored boolean for the given integer, or 0 to remove.
// Returns 0 if out of memory.
int int32trie_put(struct int32trie *, int32_t, long);

// Free all of the trie's resources and reset to zero.
void int32trie_free(struct int32trie *);

#endif
