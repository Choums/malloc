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

#include "../includes/ft_malloc.h"

void	ft_free(void* ptr)
{
	t_data* tmp = NULL;
	TYPE	type;

	if (!ptr) {
		return;
	}

	pthread_mutex_lock(&mutex);

	tmp = ptr - META_DATA; // Gets ptr pointed on MD.

	// Define type according to size.
	type = (((t_data *)ptr)->size <= TINY_SIZE) ? tiny : (((t_data *)ptr)->size <= SMALL_SIZE) ? small : large;
	printf("-- find type: %d --\n", type);

	if (tmp != large) {

	} else {
		large_free(tmp);
	}
	

	pthread_mutex_unlock(&mutex);
}