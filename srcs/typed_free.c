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

#include "../includes/ft_malloc.h"

/**
 * @brief Frees large allocation and rewire large linked list.
 * 
 * @param ptr Pointer on large mem META_DATA to be freed. 
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

// TODO: small and tiny free