/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 13:35:56 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/05 16:12:08 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_cast_char(void *arg)
{
	ft_putchar((char)arg);
}

void	put_cast_str(void *arg)
{
	ft_putstr((char*)arg);
}

void	put_cast_int(void *arg)
{
	ft_putnbr((int)arg);
}

void	put_cast_unsigned_int(void *arg)
{
	unsigned int	n;

	n = (unsigned int)arg;
	if (n / 10 > 0)
		put_cast_unsigned_int((void*)(n / 10));
	ft_putchar((n % 10) + 48);
}

void	put_cast_short(void *arg)
{
	ft_putnbr((int)arg);
}

void	put_cast_unsigned_short(void *arg)
{
	put_cast_unsigned_int((int)arg);
}

void	put_cast_long(void *arg)
{
	ft_putstr("{long}");
	//ft_putlong((long)arg);
}

void	put_cast_unsigned_long(void *arg)
{
	ft_putstr("{Ulong}");
	//ft_putulong((unsigned long)arg);
}
