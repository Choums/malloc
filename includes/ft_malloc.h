/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:09:42 by chaidel           #+#    #+#             */
/*   Updated: 2024/03/01 18:09:42 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
// #include <sys/mmap.h>
# include <sys/resource.h>
# include <sys/time.h>
# include <stdbool.h>
# include "libft.h"


/**
 *  @brief Meta-data at the beginning of each chunk containing information.
 * 	@param free Flag to mark whether it's free or not.
 *	@param size The size of the chunk.
 *	@param next Ptr to the next chunk.
 *	@param prev Ptr to previous chunk.
 */
typedef struct s_data {
	size_t size;
	struct s_data* next;
	struct s_data* prev;
	bool free;
} t_data;

#endif