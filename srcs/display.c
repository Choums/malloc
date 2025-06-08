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
	pthread_mutex_lock(&mutex);

	size_t total = 0;

	ft_printf("%sMETA DATA%s  : %x (hex)\n",BBLU, END, META_DATA);

	ft_printf("%sTINY%s  : %p : %d bytes.\n",BWHI, END, base->ptr_tiny, base->size_tiny);
	total += get_alloc_mem_type((t_data*)base->ptr_tiny);
	
	ft_printf("%sSMALL%s : %p\n",BWHI, END, base->ptr_small);
	total += get_alloc_mem_type(base->ptr_small);
	
	ft_printf("%sLARGE%s : %p\n",BWHI, END, base->ptr_large);
	total += get_alloc_mem_type(base->ptr_large);
	
	ft_printf("%sTotal%s : %d %sbytes%s.\n",BWHI, END, total, BWHI, END);

	pthread_mutex_unlock(&mutex);
}

/**
 * Get total allocation memory by type and print size of each data chunk.
 * @param head Head of meta-data type.
*/
size_t	get_alloc_mem_type(t_data* head)
{
	size_t total = 0;

	if (!head) {
		return (total);
	}
	
	while (head) {
		if (!head->free) { // Display only used mem
			ft_printf("%p - %p\t: %d bytes.\n", (void *)head + META_DATA, (void *)head + head->size, head->size); // head + META-DATA => start ptr chunk | (void*)head + META_DATA + head->size => end ptr of chunk

			total += head->size;
		}
		head = head->next;
	}

	return (total);
}