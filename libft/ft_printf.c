/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 18:15:30 by chaidel           #+#    #+#             */
/*   Updated: 2021/12/16 02:13:51 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_leaker(char c, va_list args)
{
	size_t	o;
	char	*s;

	o = 0;
	if (c == 'p')
	{
		o += ft_putstr_fd("0x", 1);
		s = ft_itoa_hexa(va_arg(args, unsigned long int), HEXA);
		o += ft_putstr_fd(s, 1);
		free(s);
	}
	else if (c == 'x')
	{
		s = ft_itoa_hexa(va_arg(args, unsigned int), HEXA);
		o += ft_putstr_fd(s, 1);
		free(s);
	}
	else if (c == 'X')
	{
		s = ft_itoa_hexa(va_arg(args, unsigned int), MHEXA);
		o += ft_putstr_fd(s, 1);
		free(s);
	}
	return (o);
}

size_t	ft_check_str(va_list args)
{
	size_t	o;
	char	*str;

	str = va_arg(args, char *);
	o = 0;
	if (str == NULL)
		o += ft_putstr_fd("(null)", 1);
	else
		o += ft_putstr_fd(str, 1);
	return (o);
}

size_t	ft_parsing(char c, va_list args)
{
	size_t	o;

	o = 0;
	if (c == 'c')
		o += ft_putchar_fd(va_arg(args, int), 1);
	else if (c == 's')
		o += ft_check_str(args);
	else if (c == 'p')
		o += ft_leaker(c, args);
	else if (c == 'd')
		o += ft_putnbr_fd(va_arg(args, int), 1);
	else if (c == 'i')
		o += ft_putnbr_fd(va_arg(args, int), 1);
	else if (c == 'u')
		o += ft_un(args);
	else if (c == 'x')
		o += ft_leaker(c, args);
	else if (c == 'X')
		o += ft_leaker(c, args);
	else if (c == '%')
		o += ft_putchar_fd(c, 1);
	return (o);
}

int	ft_printf(const char *str, ...)
{
	size_t	o;
	size_t	i;
	va_list	args;

	va_start(args, str);
	o = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			o += ft_parsing(str[i + 1], args);
			i++;
		}
		else
			o += ft_putchar_fd(str[i], 1);
		i++;
	}
	va_end(args);
	return (o);
}
