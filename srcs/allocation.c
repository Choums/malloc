/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:23:56 by chaidel           #+#    #+#             */
/*   Updated: 2024/03/18 14:56:57 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

/**
 * First call of malloc, allocate space for global heads.
*/
bool	init_base()
{
	base = mmap(0, sizeof(t_mptr), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (base == MAP_FAILED) {
		return (false);
	}

	base->ptr_tiny = NULL;
	base->ptr_small = NULL;
	base->ptr_large = NULL;
	
	base->lst_tiny = NULL;
	base->lst_small = NULL;
	base->lst_large = NULL;

	base->size_tiny = 0;
	base->size_small = 0;
	base->size_large = 0;

	return (true);
}

void* mem_alloc(size_t size)
{
	
	void* ptr = NULL;
	TYPE type;

	if (size <= 0) {
		return (ptr);
	}

	if (!base) {
		if (!init_base())
			return (NULL);
	}

	// Define allocation type according to size.
	type = (size <= TINY_ZONE) ? tiny : (size <= SMALL_ZONE) ? small : large;

	switch (type) {
	case tiny:
		printf("TINY ALLOC\n");
		// ptr = tiny_alloc //TODO: tiny alloc
		break;
	case small:
		printf("SMALL ALLOC\n");
		// ptr = small_alloc //TODO: small alloc
		break;
	case large:
		printf("LARGE ALLOC\n");
		ptr = large_alloc(size);
		break;
	}

	if (ptr == MAP_FAILED) { // Error allocation.
		return (NULL);
	}

	return (ptr + META_DATA);
}

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