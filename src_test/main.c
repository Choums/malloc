/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:15:32 by chaidel           #+#    #+#             */
/*   Updated: 2024/03/01 18:15:32 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define PAGE_SIZE (size_t)getpagesize()

#include "malloc.h"
#include <unistd.h>
#include <stdio.h>

#define ERROR -1
#define SUCCESS 0

static int tests_passed = 0;
static int tests_failed = 0;

void test_show_alloc_mem()
{
	void* ptr1 = malloc(10U);
	void* ptr2 = malloc(20U);
	void* ptr3 = malloc(30U);
	void* ptr4 = malloc(40U);
	void* ptr5 = malloc(50U);
	show_alloc_mem();
	free(ptr1);
	free(ptr3);
	free(ptr5);
	show_alloc_mem();
	void* ptr6 = malloc(5U);
	void* ptr7 = malloc(15U);
	void* ptr8 = malloc(25U);
	show_alloc_mem();
	free(ptr2);
	free(ptr4);
	free(ptr6);
	free(ptr7);
	free(ptr8);
	show_alloc_mem();
}

void test_hundred_alloc() {
	char* s1[200];
	char* s2[200];
	char* s3[3];

	for (int i = 0; i < 200; i++) {
		s1[i] = malloc(TINY_SIZE);
		s2[i] = malloc(SMALL_SIZE);
	}
	
	s3[0] = malloc(SMALL_SIZE + TINY_SIZE);
	s3[1] = malloc(SMALL_SIZE + TINY_SIZE * 2);
	s3[2] = malloc(SMALL_SIZE + TINY_SIZE * 3);
	
	show_alloc_mem();

	for (int i = 0; i < 200; i++) {
		free(s1[i]);
		free(s2[i]);
	}

	free(s3[0]);
	free(s3[1]);
	free(s3[2]);
	show_alloc_mem();
}

void test_realloc() {
	char* ptr = malloc(10);
	show_alloc_mem();
	ptr = realloc(ptr, 5);
	show_alloc_mem();
	ptr = realloc(ptr, 50);
	show_alloc_mem();
	free(ptr);
}

void simple_realloc()
{
	char* ptr = (char*)malloc(sizeof(char) * (strlen("Hello, World!") + 1));
	strcpy(ptr, "Hello, World!\0");
	show_alloc_mem();
	ft_printf("[%s::%d] 👉 \"%s\"\n", __func__, __LINE__, ptr);

	char* ptr2 = (char*)realloc(ptr, sizeof(char) * (strlen("Hello") + 1));
	ptr2[strlen("Hello")] = '\0';
	printf("[%s::%d] 👉 \"%s\"\n", __func__, __LINE__, ptr2);
	show_alloc_mem();

	char* ptr3 = (char*)realloc(ptr2, sizeof(char) * (strlen("Hello, Woooooooooorld !") + 1));
	strcpy(ptr3, "Hello, Woooooooooorld !\0");
	ft_printf("[%s::%d] 👉 \"%s\"\n", __func__, __LINE__, ptr3);
	show_alloc_mem();

	free(ptr3);
}

void test_write() {
	char* ptr = malloc(27);
	for (int i = 0; i < 27; i++) {
		ptr[i] = 'A' + i % 26;
	}
	ptr[26] = '\0';
	show_alloc_mem();
	ft_printf("[%s::%d] 👉 \"%s\"\n", __func__, __LINE__, ptr);

	ptr = realloc(ptr, 53);
	for (int i = 0; i < 53; i++) {
		ptr[i] = 'a' + i % 26;
	}
	ptr[52] = '\0';
	show_alloc_mem();
	ft_printf("[%s::%d] 👉 \"%s\"\n", __func__, __LINE__, ptr);

	free(ptr);
}

void test_realloc_null() {
	char* ptr = realloc(NULL, 10); // Should behave like malloc(10)
	show_alloc_mem();

	void* nul = realloc(ptr, 0); // Should behave like free(ptr)
	show_alloc_mem();
	free(nul);
	show_alloc_mem();
}

void big_malloc_test() {
	size_t total = 2000000000U; // 2GB
	ft_printf("[%s::%d] 👉 %i\n", __func__, __LINE__, total);
	void* big = malloc(total);
	show_alloc_mem();
	free(big);
	show_alloc_mem();
}

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
	char *p = malloc(oldsz);
	ASSERT(p != NULL, "malloc returns non-NULL for realloc grow test");
	if (!p) return;
	char pattern[oldsz];
	for (size_t i = 0; i < oldsz - 1; i++) {
		pattern[i] = (char)('A');
		p[i] = pattern[i];
	}
	char *q = realloc(p, newsz);
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
	// ft_printf("Tiny size: %u\n", TINY_SIZE);
	// ft_printf("Small size: %u\n", SMALL_SIZE);

	// test_show_alloc_mem();
	// test_hundred_alloc();
	// test_realloc();
	simple_realloc();
	// test_write();
	// test_realloc_null();
	// big_malloc_test();


	// ---------------------------------------------------------------------------- //

	// printf("%sReimplemented Malloc\n\n%s", BBLU, END);
	// printf("Running allocator automatic tests...\n");
    // test_malloc_basic();
    // test_realloc_grow_preserve();
    // test_realloc_shrink_preserve();
    // test_realloc_null_behaves_like_malloc();

    // printf("\nSummary: %d passed, %d failed\n\n", tests_passed, tests_failed);

	return (0);
}