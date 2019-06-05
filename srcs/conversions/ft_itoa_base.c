/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivie <maolivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 16:06:01 by maolivie          #+#    #+#             */
/*   Updated: 2019/06/05 16:09:52 by maolivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>

size_t	nbr_len(unsigned int value, int base)
{
	size_t	len;

	len = 1;
	if (base == 10 && (int)value < 0)
	{
		++len;
		value = -(int)value;
	}
	while (value >= (unsigned int)base)
	{
		++len;
		value /= base;
	}
	return (len);
}

char	get_digit(unsigned int value)
{
	return (value > 9 ? 'A' + value - 10 : '0' + value);
}

char	*ft_itoa_base(unsigned int value, int base)
{
	size_t	len;
	char	*str;

	len = nbr_len(value, base);
	if ((str = ft_strnew(len)) == NULL)
		return (NULL);
	if (base == 10 && (int)value < 0)
	{
		str[0] = '-';
		value = -(int)value;
	}
	while (value >= (unsigned int)base)
	{
		str[--len] = get_digit(value % base);
		value /= base;
	}
	str[--len] = get_digit(value);
	return (str);
}
