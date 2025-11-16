/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 19:09:27 by marvin            #+#    #+#             */
/*   Updated: 2025/11/15 19:09:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		*calloc(size_t count, size_t size)
{
	void	*ptr;
	int		total_sz;
	int		i;

	if (!(ptr = malloc(count * size)))
		return (NULL);
	total_sz = (((count * size) - 1) >> 3) + 1;
	i = -1;
	while (++i < total_sz)
		((int64_t*)ptr)[i] = 0;
	return (ptr);
}