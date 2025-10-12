/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:26:44 by chaidel           #+#    #+#             */
/*   Updated: 2024/03/23 16:26:44 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	free(void* ptr)
{
	t_data* tmp = NULL;
	TYPE	type;

	if (!ptr) {
		return;
	}

	tmp = ptr - META_DATA; // Gets ptr pointed on MD.

	// Define type according to size.
	type = (tmp->size <= TINY_SIZE) ? TINY : (tmp->size <= SMALL_SIZE) ? SMALL : LARGE;

	if (type != LARGE) {
		tiny_small_free(tmp, type);
	} else {
		large_free(tmp);
	}
}