/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivie <maolivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 16:06:01 by maolivie          #+#    #+#             */
/*   Updated: 2019/06/05 11:30:36 by maolivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>

unsigned short	nbr_len(int value, int base)
{
	unsigned int	abs;
	unsigned short	len;

	len = 1;
	if (value < 0)
	{
		abs = -value;
		if (base == 10)
			++len;
	}
	else
		abs = value;
	while (abs >= (unsigned int)base)
	{
		++len;
		abs /= base;
	}
	return (len);
}

char			get_sign(short value)
{
	return (value > 9 ? 'A' + value - 10 : '0' + value);
}

char			*ft_itoa_base(int value, int base)
{
	char			*str;
	unsigned int	abs;
	unsigned short	len;

	len = nbr_len(value, base);
	if ((str = ft_strnew(len)) == NULL)
		return (NULL);
	if (value < 0)
	{
		abs = -value;
		if (base == 10)
			str[0] = '-';
	}
	else
		abs = value;
	while (abs >= (unsigned int)base)
	{
		str[--len] = get_sign(abs % base);
		abs /= base;
	}
	str[--len] = get_sign(abs);
	return (str);
}
