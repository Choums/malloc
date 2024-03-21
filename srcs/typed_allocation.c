/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typed_allocation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:09:25 by chaidel           #+#    #+#             */
/*   Updated: 2024/03/21 18:47:20 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

/**
 * Allocate memory for a large malloc.
 * @param size Requested size.
 * @note Large mallocs will be in a zone of ```size```.
*/
void* large_alloc(size_t size)
{
	void* ptr = NULL;

	if (base->ptr_large == NULL) { // head null => alloc will be head.
		ptr = mmap(0, META_DATA + size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1 , 0);
		if (ptr == MAP_FAILED) {
			return (ptr);
		}
		
		/* init global on head and last (1st call)*/
		base->ptr_large = ptr;
		base->lst_large = ptr;

		/* init meta */
		((t_data *)base->ptr_large)->size = size;
		((t_data *)base->ptr_large)->free = false;
		((t_data *)base->ptr_large)->next = NULL;
		((t_data *)base->ptr_large)->prev = NULL;

	} else { // add alloc as last.
		ptr = mmap(0, META_DATA + size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1 , 0);
		if (ptr == MAP_FAILED) {
			return (ptr);
		}
		
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
 * Allocate memory for a large malloc.
 * @param size Requested size.
*/
void*	tiny_alloc(size_t size)
{
	void* ptr = NULL;

	if (base->ptr_tiny == NULL) { // Head null => alloc type
		if (!init_zones(tiny))
			return (ptr);
	}



	return (ptr);
}

/**
 * Allocate memory for a small malloc.
 * @param size Requested size.
*/
void*	small_alloc(size_t size)
{
	void*	ptr = NULL;

	if (base->ptr_small == NULL) { // Head null => alloc type
		if (!init_zones(small))
			return (ptr);
	}
	
	ptr = get_free_block(base->ptr_small, size);
	if (ptr) // fitting chunk found
	{
		(t_data *)ptr->free = false;
		
		if (((t_data *)ptr->size - size - META_DATA) > (META_DATA + SMALL_SIZE)) { // Unused space will be a new block
			printf("%s--- Spliting ! ---%s\n", BRED, END);
			split_blocks(ptr, size, &(base->lst_small));
		}
		
	} else { // Allocate a new zone
		
	}
	
	return (ptr);
}