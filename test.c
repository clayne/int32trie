#include <stdio.h>
#include "int32trie.h"

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
    struct int32trie t[] = {{0, 0, 0}};
    for (int j = 0; j < 16; j++) {
        uint32_t k = triple32(-j);
        for (long i = 0; i < 1L<<20; i++) {
            int32trie_put(t, triple32(i^k), 1 + i%1000);
        }

        for (long i = 0; i < 1L<<20; i++) {
            int expect = 1 + i%1000;
            if (int32trie_get(t, triple32(i^k)) != expect) {
                printf("FAIL %08lx != %d\n", (long)triple32(i), expect);
                int32trie_free(t);
                return 1;
            }
        }

        for (long i = 1L<<20; i < 1L<<21; i++) {
            if (int32trie_get(t, triple32(i))) {
                printf("FAIL %08lx != 0\n", (long)triple32(i));
                int32trie_free(t);
                return 1;
            }
        }
        int32trie_free(t);
    }
    puts("PASS");
    return 0;
}
