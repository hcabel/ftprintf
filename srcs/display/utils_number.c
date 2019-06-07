/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 12:24:19 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/07 16:12:14 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	putnnbr(long long n)
{
	unsigned long long abs;

	if (n < 0)
	{
		abs = -n;
		ft_putchar('-');
	}
	else
		abs = n;
	if (abs >= 10)
		putnnbr(abs / 10);
	ft_putchar(abs % 10 + '0');
}

void		show_nbr(long long n, int scale)
{
	int	size;

	size = count_nu(n);
	if (scale > size)
		fill('0', scale - size);
	putnnbr(n);
}

long long	count_nu(long long nb)
{
	long long	i;
	long long	n;

	n = nb;
	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		if (n == -2147483648)
			return (1);
		i++;
		nb *= -1;
	}
	while (nb > 0)
	{
		i++;
		nb /= 10;
	}
	return (i);
}