/* This is free and unencumbered software released into the public domain. */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "int32trie.h"

static uint32_t
int32trie_new(struct int32trie *t)
{
    if (t->len == t->cap) {
        uint32_t cap = t->cap ? t->cap *= 2: 16;
        if (!cap || !(cap*sizeof(t->nodes[0]))) {
            return -1;
        }
        void *p = realloc(t->nodes, cap*sizeof(t->nodes[0]));
        if (!p) {
            return -1;
        }
        t->cap = cap;
        t->nodes = p;
    }
    uint32_t i = t->len++;
    memset(&t->nodes[i], 0, sizeof(t->nodes[i]));
    return i;
}

long
int32trie_get(const struct int32trie *t, int32_t x)
{
    if (!t->len) return 0;
    uint32_t u = x;
    uint32_t n = 0;
    for (int i = 7; i >= 0; i--) {
        int v = u >> (i*4) & 0xf;
        n = t->nodes[n].child[v];
        if (!n) return 0;
    }
    return t->nodes[n].value;
}

int
int32trie_put(struct int32trie *t, int32_t x, long value)
{
    if (!t->len && int32trie_new(t)) {
        return 0;
    }
    uint32_t u = x;
    uint32_t n = 0;
    for (int i = 7; i >= 0; i--) {
        int v = u >> (i*4) & 0xf;
        uint32_t m = t->nodes[n].child[v];
        if (!m) {
            m = int32trie_new(t);
            if (m == (uint32_t)-1) {
                return 0;
            }
            t->nodes[n].child[v] = m;
        }
        n = m;
    }
    t->nodes[n].value = value;
    return 1;
}

void
int32trie_free(struct int32trie *t)
{
    free(t->nodes);
    t->cap = t->len = 0;
    t->nodes = 0;
}
