/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:47:40 by chaidel           #+#    #+#             */
/*   Updated: 2024/03/17 17:40:07 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	ft_get_len_hexa(long int number)
{
	int	len;

	len = 0;
	while (number > 0)
	{
		number /= 16;
		len++;
	}
	return (len);
}

static void	ft_put_neg(int *sign, long int *number)
{
	*sign = 1;
	*number = -(*number);
}

char	*ft_itoa_hexa(long int number, char *base)
{
	int		sign;
	int		len;
	char	*str;

	sign = 0;
	if (number == 0)
		return (ft_strdup("0"));
	if (number < 0)
	{
		len = ft_get_len_hexa(-number) + 1;
		ft_put_neg(&sign, &number);
	}
	else
		len = ft_get_len_hexa(number);
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (--len >= sign)
	{
		str[len] = base[number % 16];
		number /= 16;
	}
	if (sign)
		str[len] = '-';
	return (str);
}
