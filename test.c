#include <stdio.h>
#include "uint32trie.h"

static uint32_t
triple32(uint32_t x)
{
    x ^= x >> 17; x *= 0xed5ad4bb;
    x ^= x >> 11; x *= 0xac4c1b51;
    x ^= x >> 15; x *= 0x31848bab;
    x ^= x >> 14;
    return x;
}

int
main(void)
{
    struct uint32trie t[] = {{0, 0, 0}};
    for (int j = 0; j < 16; j++) {
        uint32_t k = triple32(-j);
        for (long i = 0; i < 1L<<20; i++) {
            trie_put(t, triple32(i^k), 1 + i%2);
        }

        for (long i = 0; i < 1L<<20; i++) {
            if (trie_get(t, triple32(i^k)) != 1 + i%2) {
                printf("FAIL %08lx != %ld\n", (long)triple32(i), 1 + i%2);
                trie_free(t);
                return 1;
            }
        }

        for (long i = 1L<<20; i < 1L<<21; i++) {
            if (trie_get(t, triple32(i))) {
                printf("FAIL %08lx != 0\n", (long)triple32(i));
                trie_free(t);
                return 1;
            }
        }
        trie_free(t);
    }
    puts("PASS");
    return 0;
}
