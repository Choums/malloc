
# define PAGE_SIZE (size_t)getpagesize()

#include "malloc.h"
#include <unistd.h>
#include <stdio.h>

static int tests_passed = 0;
static int tests_failed = 0;

void test_malloc_basic(void)
{
    const size_t size = 64;
    char *p = malloc(size);
    ASSERT(p != NULL, "malloc returns non-NULL for size 64");
    if (p) {
        for (size_t i = 0; i < size; i++) p[i] = (char)(i & 0xff);
        for (size_t i = 0; i < size; i++) {
            if (p[i] != (char)(i & 0xff)) {
                ASSERT(0, "malloc memory writable and readable");
                free(p);
                return;
            }
        }
        ASSERT(1, "malloc memory writable and readable");
        free(p);
    }
}

void test_realloc_grow_preserve(void)
{
    size_t oldsz = 32;
    size_t newsz = 128;
	unsigned char *p = malloc(oldsz);
	ASSERT(p != NULL, "malloc returns non-NULL for realloc grow test");
	if (!p) return;
	unsigned char pattern[oldsz];
	for (size_t i = 0; i < oldsz; i++) {
		pattern[i] = (unsigned char)('A' + (i % 26));
		p[i] = pattern[i];
	}
	unsigned char *q = realloc(p, newsz);
	ASSERT(q != NULL, "realloc growing returns non-NULL");
	if (!q) return;
	int ok = memcmp(q, pattern, oldsz) == 0;
	ASSERT(ok, "realloc preserved previous contents when growing");
	free(q);
}

void test_realloc_shrink_preserve(void)
{
    size_t start = 128;
    size_t shrink = 32;
	unsigned char *p = malloc(start);
	ASSERT(p != NULL, "malloc returns non-NULL for realloc shrink test");
	if (!p) return;
	unsigned char pattern[start];
	for (size_t i = 0; i < start; i++) {
		pattern[i] = (unsigned char)('0' + (i % 10));
		p[i] = pattern[i];
	}
	unsigned char *q = realloc(p, shrink);
	ASSERT(q != NULL, "realloc shrinking returns non-NULL (or same ptr)");
	if (!q) return;
	int ok = memcmp(q, pattern, shrink) == 0;
	ASSERT(ok, "realloc preserved prefix when shrinking");
	free(q);
}

void test_realloc_null_behaves_like_malloc(void)
{
    char *p = realloc(NULL, 50);
    ASSERT(p != NULL, "realloc(NULL, size) behaves like malloc (non-NULL)");
    if (p) free(p);
}

int main(void) {
    printf("%sSystem Malloc\n\n%s", BPUR, END);
	printf("Running allocator automatic tests...\n");
    test_malloc_basic();
    test_realloc_grow_preserve();
    test_realloc_shrink_preserve();
    test_realloc_null_behaves_like_malloc();

    printf("\nSummary: %d passed, %d failed\n\n", tests_passed, tests_failed);

	return (0);
}