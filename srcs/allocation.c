/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:23:56 by chaidel           #+#    #+#             */
/*   Updated: 2024/03/18 17:13:07 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

/**
 * @brief Align the ```size``` of the memory block to the meta-data struct on 8 bytes (64 bits).
 * @param size neccessary memory block.
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


/**
 * Init only Tiny or Small zones.
*/
bool	init_zones(TYPE type)
{
	if (type == large) {
		return (false);
	}

	if (type == tiny) {
		base->ptr_tiny = mmap(0, TINY_ZONE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1 , 0);
		if (base->ptr_tiny == MAP_FAILED) {
			return (false);
		}
	
		

	} else {
		base->ptr_small = mmap(0, SMALL_ZONE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1 , 0);
		if (base->ptr_small == MAP_FAILED) {
			return (false);
		}
	}



	return (true);
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
	type = (size <= TINY_ZONE) ? tiny : (size <= SMALL_ZONE) ? small : large;

	switch (type) {
	case tiny:
		printf("TINY ALLOC\n");
		ptr = tiny_alloc(size);
		break;
	case small:
		printf("SMALL ALLOC\n");
		ptr = small_alloc(size);
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