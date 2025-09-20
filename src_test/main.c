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

#include "ft_malloc.h"
#include <unistd.h>
#include <stdio.h>

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

	for (int i = 0; i < 200; i++) {
		s1[i] = malloc(TINY_SIZE);
		s2[i] = malloc(SMALL_SIZE);
	}
	show_alloc_mem();

	for (int i = 0; i < 200; i++) {
		free(s1[i]);
		free(s2[i]);
	}
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

int main(void) {
	// ft_printf("Tiny size: %u\n", TINY_SIZE);
	// ft_printf("Small size: %u\n", SMALL_SIZE);

	test_show_alloc_mem();
	test_hundred_alloc();
	test_realloc();
	return (0);
}