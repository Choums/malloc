/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:16:54 by chaidel           #+#    #+#             */
/*   Updated: 2024/03/15 18:06:14 by chaidel          ###   ########.fr       */
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

t_mptr* base  = NULL;

void* ft_malloc(size_t size)
{
	void* ptr;
	
	if (!base)
		pthread_mutex_init(&mutex, NULL);
	pthread_mutex_lock(&mutex);

	ptr = mem_alloc(size);
	
	pthread_mutex_unlock(&mutex);
	
	return (ptr);
}