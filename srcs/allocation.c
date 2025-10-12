/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:23:56 by chaidel           #+#    #+#             */
/*   Updated: 2025/09/28 14:52:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

/**
 * @brief Align the ```size``` of the memory chunk to the meta-data struct on 8 bytes (64 bits).
 * @param size neccessary memory chunk.
 * @return Aligned size.
 * @note Given any positive integer dividing it by four	and then multiplying it by
 * 		four again results in the nearest smaller multiple of four, thus to obtain
 *		the nearest greater multiple of four we only need to add four to it.
 *		Since size_t type is 8 bytes long, the formula is modified to work with it.
 *		(bit-shifting (>> and <<) are faster than using the operators).
 *		(bit-shifting by 3 comes to 2^3 or 8).
*/
size_t align8(size_t size)
{
	return (((((size - 1) >> 3) << 3)) + 8);
}

t_mptr* base  = NULL;
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

	base->size_tiny = 0U;
	base->size_small = 0U;
	base->size_large = 0U;

	return (true);
}


/**
 * @brief Allocate a first zone Tiny or Small AND init global struct ```t_mptr``` (```base```).
*/
bool	init_zones(TYPE type)
{
	if (type == LARGE) {
		return (false);
	}

	if (type == TINY) {
		base->ptr_tiny = mmap(0, TINY_ZONE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1 , 0);
		if (base->ptr_tiny == MAP_FAILED) {
			return (false);
		}
		base->size_tiny = TINY_ZONE;
		
		((t_data *)base->ptr_tiny)->free = true;
		((t_data *)base->ptr_tiny)->head = true;
		((t_data *)base->ptr_tiny)->size = TINY_ZONE - META_DATA;
		((t_data *)base->ptr_tiny)->prev = NULL;
		((t_data *)base->ptr_tiny)->next = NULL;
		
		base->lst_tiny = base->ptr_tiny;
		// printf("ptr->size = %lu\n", TINY_ZONE - META_DATA);

	} else {
		base->ptr_small = mmap(0, SMALL_ZONE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1 , 0);
		if (base->ptr_small == MAP_FAILED) {
			return (false);
		}
		base->size_small = SMALL_ZONE;
		base->lst_small = base->ptr_small;
		
		((t_data *)base->ptr_small)->free = true;
		((t_data *)base->ptr_small)->head = true;
		((t_data *)base->ptr_small)->size = SMALL_ZONE - META_DATA;
	}

	return (true);
}

/**
 * @brief Allocate a new zone of type Tiny or Small, update total size of allocation and init the new chunk.
 * 
 * @param type Type of allocation, ```TINY``` OR ```SMALL```.
 * @return ```ptr``` on first chunk of newly allocated zone.
 */
void*	alloc_new_zone(TYPE type)
{
	void* ptr = NULL;

	if (type == LARGE) {
		return (NULL);
	}

	if (type == TINY) {
		ptr = mmap(0, TINY_ZONE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1 , 0);
		if (ptr == MAP_FAILED) {
			return (NULL);
		}
		base->size_tiny += TINY_ZONE;

		/* init meta */
		((t_data *)ptr)->size = TINY_ZONE - META_DATA;
		((t_data *)ptr)->free = true;
		((t_data *)ptr)->head = true;
		((t_data *)ptr)->next = NULL;

		t_data* last = lst_last_base((t_data *)(base->lst_tiny)); // Make the last chunk point on the new one.
		last->next = (t_data *)ptr;
		((t_data *)ptr)->prev = last;

		base->lst_tiny = ptr;
	} else {
		ptr = mmap(0, SMALL_ZONE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1 , 0);
		if (ptr == MAP_FAILED) {
			return (NULL);
		}
		base->size_small += SMALL_ZONE;

		/* init meta */
		((t_data *)ptr)->size = SMALL_ZONE - META_DATA;
		((t_data *)ptr)->free = true;
		((t_data *)ptr)->head = true;
		((t_data *)ptr)->next = NULL;

		t_data* last = lst_last_base((t_data *)(base->lst_small)); // Make the last chunk point on the new one.
		last->next = (t_data *)ptr;
		((t_data *)ptr)->prev = last;
		
		base->lst_small = ptr;
	}

	return (ptr);
}

void* mem_alloc(size_t size)
{
	
	void* ptr = NULL;
	TYPE type;

	if (size <= 0) {
		return (ptr);
	}

	size = align8(size);

	if (!base) {
		if (!init_base())
			return (NULL);
	}
	
	// Define allocation type according to size.
	type = (size <= TINY_SIZE) ? TINY : (size <= SMALL_SIZE) ? SMALL : LARGE;

	switch (type) {
	case TINY:
		ptr = tiny_alloc(size);
		break;
	case SMALL:
		ptr = small_alloc(size);
		break;
	case LARGE:
		ptr = large_alloc(size);
		break;
	}

	if (!ptr || ptr == MAP_FAILED) { // Error allocation.
		return (NULL);
	}

	return (ptr + META_DATA);
}