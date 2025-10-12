/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:15:52 by chaidel           #+#    #+#             */
/*   Updated: 2025/09/28 14:49:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

/**
 * Go over the list of chunks until one is free and wide enough.
 * @param head Head of a type. (```base->ptr_```)
 * @param size Minimal size for the chunk.
 * @return Pointer on a free and fitting chunk, OR ```NULL```.
*/
t_data*	get_free_block(t_data* head, size_t size)
{
	t_data* cur = head;

	if (head)
		while (cur && !(cur->free && cur->size >= size))
			cur = cur->next;
	return (cur);
}

/**
 * @brief Go over the list of chunks until it finds the right chunk.
 * 
 * @param ptr Pointer on chunk's data.
 * @return ptr on ```META_DATA``` of the seeked chunk.
 */
t_data*	find_block(void* ptr)
{
	ptr = ptr - META_DATA; // Gets ptr pointed on MD.
	
	return ((t_data *)ptr);
}