/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:15:52 by chaidel           #+#    #+#             */
/*   Updated: 2024/03/18 15:17:30 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"
/**
 * Go over the list of chunks until one is free and wide enough.
 * @param head Head of a type. (```base->ptr_```)
 * @param size Minimal size for the chunk.
 * @return Pointer on a fitting chunk, OR ```NULL```.
*/
t_data*	get_free_block(t_data* head, size_t size)
{
	t_data* cur = head;
	
	if (head)
		while (cur && !(cur->free && cur->size >= size))
			cur = cur->next;	
	return (cur);
}