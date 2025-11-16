/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typed_allocation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:09:25 by chaidel           #+#    #+#             */
/*   Updated: 2025/11/15 20:43:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

/**
 * Allocate memory for a LARGE malloc.
 * @param size Requested size.
 * @note Large mallocs will be in a zone of ```size```.
*/
void* large_alloc(size_t size)
{
	void* ptr = NULL;

	ptr = mmap(0, META_DATA + size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1 , 0);
	if (ptr == MAP_FAILED) {
		return (ptr);
	}

	if (base->ptr_large == NULL) { // head null => alloc will be head.
		/* init global on head and last (1st call)*/
		base->ptr_large = ptr;
		base->lst_large = ptr;

		/* init meta */
		((t_data *)base->ptr_large)->size = size;
		((t_data *)base->ptr_large)->free = false;
		((t_data *)base->ptr_large)->next = NULL;
		((t_data *)base->ptr_large)->prev = NULL;

	} else { // add alloc as last.
		/* init meta */
		((t_data *)ptr)->size = size;
		((t_data *)ptr)->free = false;
		((t_data *)ptr)->next = NULL;
		
		/* change current last with the new mem */
		((t_data *)ptr)->prev = ((t_data *)base->lst_large);
		((t_data *)base->lst_large)->next = (t_data *)ptr;

		base->lst_large = ptr;
	}

	return (ptr);
}

/**
 * Allocate memory for a TINY malloc.
 * @param size Requested size.
 * @return ```ptr``` on a chunk of requested size.
 * @note Recursive is set to split the chunk inside the newly allocated zone.
 * 	
*/
void*	tiny_alloc(size_t size)
{
	t_data* ptr = NULL;

	if (base->ptr_tiny == NULL) { // Head null => alloc type
		if (!init_zones(TINY))
			return (ptr);
	}
	ptr = get_free_block(base->ptr_tiny, size);

	if (ptr) // fitting chunk found
	{
		ptr->free = false;

		if ((ptr->size - size) > (META_DATA)) { // Unused space will be a new chunk.
			// printf("%s--- Spliting Tiny ! --- ptr->size:%lu, reqSize:%lu, META: %lu%s\n", BRED, ((t_data *)ptr)->size, size, META_DATA,END);

			split_blocks(ptr, size);
		}
		
	} else { // Allocate a new zone
		// printf("%s--- Allocating Tiny ! ---%s\n", BRED, END);
		if (alloc_new_zone(TINY) == MAP_FAILED) {
			return (NULL);
		}
		return (tiny_alloc(size)); // Recursion to split the chunk from allocation.
	}

	return (ptr);
}

/**
 * Allocate memory for a SMALL malloc.
 * @param size Requested size.
 * @return ```ptr``` on a chunk of requested size.
 * @note Recursive is set to split the chunk inside the newly allocated zone.
 * 	
*/
void*	small_alloc(size_t size)
{
	t_data*	ptr = NULL;

	if (base->ptr_small == NULL) { // Head null => first alloc type.
		if (!init_zones(SMALL))
			return (ptr);
	}
	
	ptr = get_free_block(base->ptr_small, size);
	
	if (ptr) // fitting chunk found
	{
		ptr->free = false;

		if ((ptr->size - size ) > (META_DATA)) { // Unused space will be a new chunk.

			split_blocks(ptr, size);
		}
		
	} else { // Allocate a new zone
		if (alloc_new_zone(SMALL) == MAP_FAILED) {
			return (NULL);
		}
		return (small_alloc(size)); // Recursion to split the chunk from allocation.
	}
	
	return (ptr);
}