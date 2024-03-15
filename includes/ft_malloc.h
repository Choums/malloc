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
# include <sys/mman.h>
# include <sys/resource.h>
# include <sys/time.h>
# include <stdbool.h>
# include <pthread.h>
# include "libft.h"


# define TINY_SIZE	256
# define SMALL_SIZE	4096

# define TINY_ZONE	(size_t)(META_DATA + TINY_SIZE) * 100
# define SMALL_ZONE	(size_t)(META_DATA + SMALL_SIZE) * 100

/**
 * Define mallocated region by categories.
 * @param tiny “TINY" mallocs, from 1 to 256 bytes, will be stored in TINY_ZONE bytes big zones.
 * @param small “SMALL” mallocs, from (256 + 1) to 4096 bytes, will be stored in SMALL_ZONE bytes big zones.
 * @param large “LARGE” mallocs, fron (4096 + 1) bytes and more, will be stored out of zone.
 * @note Large mallocs will be in a zone on their own.
*/
typedef enum TYPE {
	tiny,
	small,
	large
} TYPE;

/**
 * Head pointers of meta-data linked list and their sizes.
*/
typedef struct mptr {
	void*	ptr_tiny;
	void*	ptr_small;
	void*	ptr_large;
	// size_t	size_tiny;
	// size_t	size_small;
	// size_t	size_large;
} t_mptr;

/**
 * Global variable on heads of mallocated regions.
*/
extern t_mptr* base;

/**
 *  @brief Header block before each chunks containing information.
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

/**
 * Size of meta-data (header) information.
*/
# define META_DATA sizeof(t_data)

/**
 * Thread safety.
*/
extern pthread_mutex_t mutex;

void*	ft_malloc(size_t size);
void*	mem_alloc(size_t size);
int		init_base(void);
// void*	tiny_alloc(size_t size, TYPE type);
// void*	small_alloc(size_t size, TYPE type);
void*	large_alloc(size_t size);

#endif