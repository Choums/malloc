/* ************************************************************************** */
/*                                                                            */
/*                                                        :::       ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:16:54 by chaidel           #+#    #+#             */
/*   Updated: 2024/03/18 17:12:19 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static t_mptr base_instance;
t_mptr* base = &base_instance;

void* malloc(size_t size)
{
	void* ptr;

	ptr = mem_alloc(size);
	
	return (ptr);
}