/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:33:06 by chaidel           #+#    #+#             */
/*   Updated: 2024/03/21 17:33:06 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

/**
 * @brief When a chunk is wide enough to held the asked size plus a new chunk 
 * (at least ```META_DATA``` + ```TINY_SIZE```), we insert a new chunk in the list.
 * 
 * @param ptr Pointer on block to be split.
 * @param req_size Requested size during allocation.
 * @param last Last block of a type.
 */
void	split_blocks(t_data* ptr, size_t req_size, t_data** last)
{
	t_data*	new; // Unused space to be a block.
	t_data*	next; // Saves next block after the new.

	new = (void *)ptr + META_DATA + req_size; // Point on unused space start.
	next = ptr->next;
	ptr->next = new;

	/* Mis a jour des meta du nouveau block */
	new->size = ptr->size - req_size - META_DATA;
	new->free = true;
	new->next = next;
	new->prev = ptr;

	ptr->size = req_size; // Mis a jour du block demandé.

	if (next) {
		next->prev = new;
	} else { // Add the new block as last of the list.
		last = new;
	}
}