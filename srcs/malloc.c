/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:16:54 by chaidel           #+#    #+#             */
/*   Updated: 2024/03/18 17:12:19 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

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