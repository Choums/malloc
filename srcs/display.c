/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:20:50 by chaidel           #+#    #+#             */
/*   Updated: 2025/09/28 14:49:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

/**
 * Visual on the state of the allocated memory zones.
*/
void	show_alloc_mem()
{
	if (!base) {
		// ft_printf("%sbase is not initialized yet !%s\n", BRED, END);
		return ;
	}
	int total = 0;

	bool meta = true;
	if (meta)
		ft_printf("%sMETA DATA%s  : %x (hex) / %u (int)\n",BBLU, END, META_DATA, META_DATA);

	ft_printf("%sTINY%s  : %p\n",BYEL, END, (base->ptr_tiny != NULL ? base->ptr_tiny : NULL));
	total += get_alloc_mem_type((t_data*)base->ptr_tiny);

	ft_printf("%sSMALL%s : %p\n",BYEL, END, (base->ptr_small != NULL ? base->ptr_small : NULL));
	total += get_alloc_mem_type(base->ptr_small);

	ft_printf("%sLARGE%s : %p\n",BYEL, END, (base->ptr_large != NULL ? base->ptr_large : NULL));
	total += get_alloc_mem_type(base->ptr_large);

	ft_printf("%sTotal%s : %i %sbytes%s.\n",BWHI, END, total, BWHI, END);
	if (meta)
		ft_printf("-------------------------------------------------------\n");

}

/**
 * Get total allocation memory by type and print size of each data chunk.
 * @param head Head of meta-data type.
*/
size_t	get_alloc_mem_type(t_data* head)
{
	size_t total = 0;
	bool val = false;
	bool freee = true;
	bool index = true;
	
	if (!head) {
		return (total);
	}
	int i = 0;
	while (head) {
		i++;
		if (index)
			if (freee)
				ft_printf("[%d]\t", i);
		if (!head->free) { // Display only used mem
			ft_printf("%p - %p\t: %u bytes. ", (void *)head + META_DATA, (void *)head + META_DATA + head->size, head->size); // head + META-DATA => start ptr chunk | (void*)head + META_DATA + head->size => end ptr of chunk
			if (head->head && index)
				ft_printf("%sHEAD !%s%s", RED, RED, END);
			if (val)
				ft_printf("\t|-> %s\n", get_value((void *)head + META_DATA, (void *)head + META_DATA + head->size));
			ft_printf("\n");
			total += head->size;
		}
		if (head->free && freee) {
			ft_printf("%s%p - %p\t: %u bytes.%s\n", GRN, (void *)head + META_DATA, (void *)head + head->size, head->size, END);
		}
		head = head->next;
	}

	return (total);
}

// Extract the value of a memory zone between start and end (addresses).
// Returns a malloced string.
char*	get_value(void* start, void* end) {
	size_t len = (char*)end - (char*)start;
	ft_printf("len: %u\n", len);

	char* string = malloc(len + 1);
	if (!string) return NULL;

	for (size_t i = 0; i < len; i++) {
		string[i] = *((char*)start + i);
		ft_printf("[%u]%c", i, string[i]);
		if ((i+1) % 8 == 0 && i != 0) ft_printf("; "); else ft_printf(", "); // To separate every 8 bytes, to read alined memory
	}
	string[len] = '\0';

	return (string);
}