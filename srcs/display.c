/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:20:50 by chaidel           #+#    #+#             */
/*   Updated: 2024/03/22 17:38:02 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

/**
 * Visual on the state of the allocated memory zones.
*/
void	show_alloc_mem()
{
	// pthread_mutex_lock(&mutex);

	size_t total = 0;

	printf("%sMETA DATA%s  : %lx (hex) / %lu (int)\n",BBLU, END, META_DATA, META_DATA);

	printf("%sTINY%s  : %p : %li bytes.\n",BYEL, END, base->ptr_tiny, base->size_tiny);
	total += get_alloc_mem_type((t_data*)base->ptr_tiny);
	
	printf("%sSMALL%s : %p\n",BYEL, END, base->ptr_small);
	total += get_alloc_mem_type(base->ptr_small);
	
	printf("%sLARGE%s : %p\n",BYEL, END, base->ptr_large);
	total += get_alloc_mem_type(base->ptr_large);
	
	printf("%sTotal%s : %li %sbytes%s.\n",BWHI, END, total, BWHI, END);

	// pthread_mutex_unlock(&mutex);
}

/**
 * Get total allocation memory by type and print size of each data chunk.
 * @param head Head of meta-data type.
*/
size_t	get_alloc_mem_type(t_data* head)
{
	size_t total = 0;
	bool val = false;

	if (!head) {
		return (total);
	}
	int i = 0;
	while (head) {
		i++;
		printf("[%d]\t", i);
		if (!head->free) { // Display only used mem
			printf("%p - %p\t: %zd bytes. ", (void *)head + META_DATA, (void *)head + META_DATA + head->size, head->size); // head + META-DATA => start ptr chunk | (void*)head + META_DATA + head->size => end ptr of chunk
			if (head->head)
				printf("%sHEAD !%s%s\n", RED, RED, END);
			else if (val)
				printf("\t|-> %s\n", get_value((void *)head + META_DATA, (void *)head + META_DATA + head->size));
			else
				printf("\n");
			total += head->size;
		}
		if (head->free) {
			printf("%s%p - %p\t: %zu bytes.%s\n", GRN, (void *)head + META_DATA, (void *)head + head->size, head->size, END);
		}
		head = head->next;
	}

	return (total);
}

char*	get_value(void* start, void* end) {
	size_t len = (char*)end - (char*)start;
	printf("len: %zu\n", len);

	char* string = malloc(len + 1);
	if (!string) return NULL;

	for (size_t i = 0; i < len; i++) {
		string[i] = *((char*)start + i);
		printf("[%zu]%c, ", i, string[i]);
		if ((i+1) % 8 == 0 && i != 0) printf(";"); // To separate every 8 bytes, to read alined memory
	}
	string[len] = '\0';

	return (string);
}