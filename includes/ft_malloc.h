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

# define PAGE_SIZE (size_t)getpagesize()

# define TINY_SIZE	PAGE_SIZE
# define SMALL_SIZE	PAGE_SIZE * 4

# define TINY_ZONE	(size_t)(META_DATA + TINY_SIZE) * 100
# define SMALL_ZONE	(size_t)(META_DATA + SMALL_SIZE) * 100

/**
 * Define mallocated region/zone by categories.
 * @param tiny “TINY" mallocs, from 1 to 256 bytes, will be stored in ```TINY_ZONE``` bytes big zones.
 * @param small “SMALL” mallocs, from (256 + 1) to 4096 bytes, will be stored in ```SMALL_ZONE``` bytes big zones.
 * @param large “LARGE” mallocs, fron (4096 + 1) bytes and more, will be stored out of zone.
 * @note Large mallocs will be in a zone on their own.
*/
typedef enum TYPE {
	tiny,
	small,
	large
} TYPE;


struct s_mptr {
	void*	ptr_tiny;
	void*	ptr_small;
	void*	ptr_large;
	size_t	size_tiny;
	size_t	size_small;
	size_t	size_large;
	void*	lst_tiny;
	void*	lst_small;
	void*	lst_large;
};

/**
 * Head pointers of meta-data linked list and their zone size.
*/
typedef struct s_mptr t_mptr;

/**
 * Global variable on heads and tails of mallocated regions.
 * @param ptr_ Pointers on the head of the allocations (first meta).
 * @param size_ Total size of allocation type.
 * @param lst_ Pointers on the end of the allocaitons (last meta).
 * @note Head pointers of meta-data linked list and their zone size.
*/
extern t_mptr* base;

struct s_data {
	size_t size;
	struct s_data* next;
	struct s_data* prev;
	bool free;
	bool head;
};

/**
 *  @brief Header chunk/block before each chunks containing information.
 * 	@param free Flag to mark whether it's free or not.
 *	@param size The size of the chunk. !! size DOES NOT take account of the MD size !!
 *	@param head Define this alloc as the first of a zone.
 *	@param next Ptr to the next chunk.
 *	@param prev Ptr to previous chunk.
 */
typedef struct s_data t_data;

/**
 * Size of meta-data (header) information.
*/
# define META_DATA sizeof(t_data)

/** --	Thread safety.	-- **/

extern pthread_mutex_t mutex;


void*	ft_malloc(size_t size);
void	ft_free(void* ptr);

/** --	Allocation	-- **/

size_t	align8(size_t size);
void*	mem_alloc(size_t size);
bool	init_base(void);
bool	init_zones(TYPE type);
void*	alloc_new_zone(TYPE type);
void*	tiny_alloc(size_t size);
void*	small_alloc(size_t size);
void*	large_alloc(size_t size);

/** --	Free	-- **/

void	large_free(t_data* ptr);
void	tiny_small_free(t_data* ptr, TYPE type);

/** --	Display	 -- **/

void	show_alloc_mem();
size_t	get_alloc_mem_type(t_data* head);

/**	--	Finders	-- **/

t_data*	get_free_block(t_data* head, size_t size);
t_data*	find_block(void* ptr);

/**	--	Utils	-- **/

void	split_blocks(t_data* ptr, size_t req_size);
void	fusion_blocks(t_data* ptr);
t_data	*lst_last_base(t_data *lst);


#endif