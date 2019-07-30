/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 23:44:26 by hcabel            #+#    #+#             */
/*   Updated: 2019/07/30 19:31:46 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

int				add(char* add, char **str_addr, int start, int end)
{
	int		i;
	char	*str;

	str = *str_addr;
	i = 0;
	while (i < end && add[i])
	{
		str[i + start] = add[i];
		i++;
	}
	return (i);
}

int				fill(int size, char c, char **str_addr, int start)
{
	char	*str;
	int		i;

	str = * str_addr;
	i = start;
	while (i - start < size)
	{
		str[i] = c;
		i++;
	}
	return (i - start);
}

int				ft_ubaselen(unsigned long long nbr, int base)
{
	int	result;

	result = 1;
	while ((nbr /= base) > 0)
		result++;
	return (result);
}

static char		get_value(int value, char c)
{
	if (value < 10)
		return (value + '0');
	return (value + c - 10);
}

char			*ft_utoa_base(unsigned long long nbr, int base, char c)
{
	char	*result;
	int		size;
	int		i;

	size = ft_ubaselen(nbr, base);
	if (!(result = (char*)malloc(sizeof(char) * size)))
		return (NULL);
	result[size] = '\0';
	result[0] = (nbr < 0 && base <= 10 ? '-' : '\0');
	i = size - 1;
	if (nbr == 0)
	{
		result[0] = '0';
		result[1] = '\0';
	}
	while (nbr > 0)
	{
		result[i] = get_value(nbr % base, c);
		nbr /= base;
		i--;
	}
	return (result);
}
