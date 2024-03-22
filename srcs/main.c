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
	size_t len = strlen("salut ca va ?");
	char* str = (char *)ft_malloc(sizeof(char) * (len + 1));
	str = ft_memcpy(str, "salut", len);

	char* str2 = (char *)ft_malloc(sizeof(char) * SMALL_SIZE + 1);

	show_alloc_mem();
	printf("%s[%s]%s\n", BPUR, str, END);
	printf("%s[%s]%s\n", BPUR, str2, END);
	return (0);
}