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

void test_real() {
	char *addr;

	addr = malloc(16);
	show_alloc_mem();
	free(NULL);
	// free((void *)addr + 5);
	show_alloc_mem();
	if (realloc((void *)addr + 5, 10) == NULL)
		ft_printf("Bonjours\n");
}

int main(void) {
	// ft_printf("Tiny size: %u\n", TINY_SIZE);
	// ft_printf("Small size: %u\n", SMALL_SIZE);

	// test_show_alloc_mem();
	// test_hundred_alloc();
	// test_realloc();
	// test_write();
	// test_realloc_null();
	// big_malloc_test();
	test_real();
	return (0);
}