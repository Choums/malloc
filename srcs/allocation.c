/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:23:56 by chaidel           #+#    #+#             */
/*   Updated: 2024/03/17 18:02:33 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

/**
 * First call of malloc, allocate space for global heads.
*/
bool	init_base() {
	void* ptr = NULL;

	ptr = mmap(0, sizeof(t_mptr), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (ptr == MAP_FAILED) {
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
		// ptr = tiny_alloc //TODO: tiny alloc
		break;
	case small:
		// ptr = small_alloc //TODO: small alloc
		break;
	case large:
		ptr = large_alloc(size);
		break;
	}

	if (ptr == MAP_FAILED) { // Error allocation.
		return (NULL);
	}

	return (ptr);
}

void* large_alloc(size_t size)
{
	void* ptr = NULL;

	if (base->ptr_large == NULL) { // head null => alloc will be head.
		ptr = mmap(0, META_DATA + size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1 , 0);
		if (ptr == MAP_FAILED) {
			return (ptr);
		}
		base->ptr_large = ptr;
		
		// (t_data*)base->ptr_large->size = size;
		// (t_data*)base->ptr_large->free = false;
		// base->(t_data*)ptr_large->next = NULL;
	} else { // add alloc as last.
		
	}

	return (ptr);
}