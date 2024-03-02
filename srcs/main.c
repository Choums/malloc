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

#include "../includes/ft_malloc.h"

int main(void) {
	t_data x;
	x.free = true;
	x.size = 22;
	x.next = NULL;
	x.prev = NULL;
	printf("%ld: bool\n", sizeof(x.free));
	printf("%ld: size_t\n", sizeof(size_t));
	printf("%ld: ptr\n", sizeof(x.next));
	printf("%ld: ptr\n", sizeof(x.prev));
	printf("%ld\n", sizeof(x));
	return (0);
}