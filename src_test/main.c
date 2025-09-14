/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:15:32 by chaidel           #+#    #+#             */
/*   Updated: 2024/03/01 18:15:32 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define PAGE_SIZE (size_t)getpagesize()

/**
 * Size of meta-data (header) information.
*/
# define META_DATA sizeof(t_data)

# define TINY_SIZE	(PAGE_SIZE / (64))
# define SMALL_SIZE	(PAGE_SIZE / (16))

# define TINY_ZONE	(size_t)((TINY_SIZE + META_DATA) * 100)
# define SMALL_ZONE	(size_t)((SMALL_SIZE + META_DATA) * 100)

#include "ft_malloc.h"
#include <unistd.h>
#include <stdio.h>

int main(void) {

	// char	*(s1[100]);
	// for (size_t i = 0; i < 100; i++) {
	// 	s1[i] = malloc(TINY_SIZE);
	// 	ft_memmove(s1[i], "Hello World!", 13);
	// 	s1[i][13] = '\0';
	// }
	// show_alloc_mem();

	// printf("s1[50] = %s\n", s1[50]);

	// for (size_t i = 0; i < 100; i++) {
	// 	free(s1[i]);
	// }
	show_alloc_mem();

	return (0);
}