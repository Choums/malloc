/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   except.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:57:54 by chaidel           #+#    #+#             */
/*   Updated: 2024/03/17 17:42:27 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

size_t	ft_un(va_list args)
{
	size_t				o;
	unsigned long int	nb;

	o = 0;
	nb = va_arg(args, unsigned int);
	if (nb > (unsigned int)0)
		o += ft_unsigned_putnbr_fd(nb, 1);
	else if (nb == (unsigned int)-1)
		o += ft_unsigned_putnbr_fd(UINT_MAX, 1);
	else if (nb < (unsigned int)-1)
		o += ft_unsigned_putnbr_fd(UINT_MAX + nb, 1);
	return (o);
}

size_t	ft_unsigned_putnbr_fd(long int n, int fd)
{
	long int	nbr;
	size_t				len;

	len = 0;
	if (fd < 0)
		return (len);
	nbr = n;
	if (nbr < 0)
	{
		len += ft_putchar_fd('-', fd);
		nbr *= (-1);
	}
	if (nbr > 9)
	{
		len += ft_putnbr_fd(nbr / 10, fd);
		len += ft_putnbr_fd(nbr % 10, fd);
	}
	else
		len += ft_putchar_fd(nbr + '0', fd);
	return (len);
}
