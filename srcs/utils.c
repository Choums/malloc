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

#include "../includes/malloc.h"

/**
 * @brief When a chunk is wide enough to held the asked size plus a new chunk 
 * (at least ```META_DATA``` + ```TYPE_SIZE```), we insert a new chunk in the list.
 * 
 * @param ptr Pointer on chunk to be split. (must point on the meta)
 * @param req_size Requested size during allocation.
 */
void	split_blocks(t_data* ptr, size_t req_size)
{
	t_data*	new; // Unused space to be a chunk.
	t_data*	next; // Saves next chunk after the new.

	// ft_printf("split_blocks::size=%lu & allsize%lu\n", req_size, ptr->size);

	new = (void *)ptr + META_DATA + req_size; // Point on unused space start.
	next = ptr->next;
	ptr->next = new;

	/* Mis a jour des meta du nouveau chunk */
	new->size = ptr->size - req_size - META_DATA;
	new->free = true;
	new->head = false;
	new->next = next;
	new->prev = ptr;

	ptr->size = req_size; // Mis a jour du chunk demandé.

	if (next)
		next->prev = new;
}

/**
 * @brief Merge two free chunk.
 * @param ptr Pointer on a free chunk. (next chunk must be free aswell)
 */
void	fusion_blocks(t_data* ptr)
{
	// printf("--> fusion_blocks called on ptr: %p\n", ptr);
	if (ptr) {
		ptr->size += META_DATA + ptr->next->size;
		ptr->next = ptr->next->next; // Saves pointer of the chunk after the one merged.

		if (ptr->next) { // Add the curr chunk as prev
			ptr->next->prev = ptr;
		}
	}

}

t_data	*lst_last_base(t_data *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}