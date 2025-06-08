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
	// printf("%lu\n", (size_t)getpagesize());
	char*	test = "salut";
	// char*	test2 = "qsdfqsdqsdqsd";
	size_t	len = strlen(test);
	// size_t	len2 = strlen(test2);

	char*	str = (char *)ft_malloc(sizeof(char) * (len + 1 ));
	ft_strlcpy(str, test, len + 2);

	// char*	str2 = (char *)ft_malloc(sizeof(char) * (len2 + 1 ));
	// ft_strlcpy(str2, test2, len2 + 2);

	// // int* n = ft_malloc(sizeof(int) * (SMALL_SIZE));
	// // (void)n;

	// char* str2 = (char *)ft_malloc(sizeof(char) * (len + 1));
	// ft_strlcpy(str2, test, len + 1);

	// char* str3 = (char *)ft_malloc(sizeof(char) * (len + 1));
	// ft_strlcpy(str3, test, len + 1);


	// show_alloc_mem();

	// ft_free(str2);
	show_alloc_mem();
	ft_free(str);


	// printf("%s[%s]%s\t%lu bytes\n", BPUR, str, END, len);
	// printf("%s[%s]%s\t%lu bytes\n", BPUR, str2, END, len);
	// printf("%s[%s]%s\t%lu bytes\n", BPUR, str3, END, len);
	// printf("%s[%i]%s\n", BPUR, n[0], END);

	return (0);
}