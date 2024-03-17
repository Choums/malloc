/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 10:35:35 by chaidel           #+#    #+#             */
/*   Updated: 2024/03/17 17:40:21 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define HEXA "0123456789abcdef"
# define MHEXA "0123456789ABCDEF"
# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

int		ft_printf(const char *str, ...);
size_t	ft_parsing(char c, va_list args);
size_t	ft_leaker(char c, va_list args);
size_t	ft_un(va_list args);
size_t	ft_check_str(va_list args);
char	*ft_itoa_hexa(long int number, char *base);
void	*ft_calloc(size_t length, size_t type);
size_t	ft_putstr_fd(char *str, int fd);
size_t	ft_putchar_fd(char c, int fd);
size_t	ft_putnbr_fd(int n, int fd);
size_t	ft_unsigned_putnbr_fd(long int nb, int fd);
char	*ft_strdup(const char *str);

#endif
