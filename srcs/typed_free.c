/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typed_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:19:55 by chaidel           #+#    #+#             */
/*   Updated: 2024/03/23 18:19:55 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

/**
 * @brief Frees LARGE allocation and rewire LARGE linked list.
 * 
 * @param ptr Pointer on LARGE mem META_DATA to be freed. 
 */
void	large_free(t_data* ptr)
{
	if (ptr->prev && ptr->next) { // Middle case => prev and next are rewired.
		ptr->prev->next = ptr->next;
		ptr->next->prev = ptr->prev;
	}
	else if (ptr == base->ptr_large) { // First case => next will be head. (if no next then head null)
		base->ptr_large = ptr->next;
		if (ptr->next)
			ptr->next->prev = NULL;
	}
	else if (ptr == base->lst_large) { // Last case => prev will be last
		base->lst_large = ptr->prev;
		if (ptr->prev)
			ptr->prev->next = NULL;
	}

	base->size_large -= ptr->size + META_DATA; // (ptr->size + META_DATA) == Large alloc.

	munmap(ptr, ptr->size + META_DATA);
}

void	tiny_small_free(t_data* ptr, TYPE type)
{
	// ft_printf("Freeing TINY/SMALL block of size: %zu\n", ptr->size);
	ptr->free = true;

	/**	---- Prev is free ----	**/
	if (!ptr->head && ptr->prev && ptr->prev->free) {
		// printf("Prev is free !\n");
		ptr = ptr->prev; // current ptr won't "exist" after the fusion, the prev becomes now the current
		fusion_blocks(ptr);
	}

	/**	---- next is free ----	**/
	if (ptr->next && !ptr->next->head && ptr->next->free) {
		// printf("next is free !\n");
		fusion_blocks(ptr);
	}

	/**	---- End of zone ----	**/
	if (ptr->head) {
		if ((ptr->next && ptr->next->head) || (!ptr->next))
		{
			// ft_printf("End of zone !\n");
			if (type == TINY)
			{
				if (base->size_tiny > TINY_ZONE) // More than one zone allocated
				{
					/**	---- Updating base ----	**/
					if (base->ptr_tiny == ptr)
						base->ptr_tiny = ptr->next;
					else if (base->lst_tiny == ptr)
						base->lst_tiny = ptr->prev;

					/**	---- Rewiring ---- **/
					if (ptr->next)
						ptr->next->prev = ptr->prev;
					if (ptr->prev)
						ptr->prev->next = ptr->next;
					base->size_tiny -= TINY_ZONE;

					int rc = munmap(ptr, TINY_ZONE);
					if (rc != 0)
						perror("munmap(TINY_ZONE) failed\n");
				}
			} else {
				if (base->size_tiny > SMALL_ZONE)
				{
					/**	---- Updating base ----	**/
					if (base->ptr_small == ptr)
						base->ptr_small = ptr->next;
					else if (base->lst_small == ptr)
						base->lst_small = ptr->prev;
					
					/**	---- Rewiring ---- **/
					if (ptr->next)
						ptr->next->prev = ptr->prev;
					if (ptr->prev)
						ptr->prev->next = ptr->next;
					base->size_small -= SMALL_ZONE;

					int rc2 = munmap(ptr, SMALL_ZONE);
					if (rc2 != 0)
						perror("munmap(SMALL_ZONE) failed\n");
				}
			}
		}
	}
}