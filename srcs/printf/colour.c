/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylewis <sylewis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 20:02:13 by sylewis           #+#    #+#             */
/*   Updated: 2019/10/13 11:28:48 by sylewis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

void	colours(char *tab[6])
{
	tab[0] = MAGENTA;
	tab[1] = RED;
	tab[2] = YELLOW;
	tab[3] = GREEN;
	tab[4] = CYAN;
	tab[5] = BLUE;
}

int		colour_parse(char *str)
{
	int i;

	i = 0;
	if (str[i] == '{' && str[i + 2] == '}')
	{
		if (str[i + 1] == 'r')
			write(1, &RED, 6);
		else if (str[i + 1] == 'g')
			write(1, &GREEN, 6);
		else if (str[i + 1] == 'y')
			write(1, &YELLOW, 6);
		else if (str[i + 1] == 'b')
			write(1, &BLUE, 6);
		else if (str[i + 1] == 'm')
			write(1, &MAGENTA, 6);
		else if (str[i + 1] == 'c')
			write(1, &CYAN, 6);
		else if (str[i + 1] == '/')
			write(1, &RESET, 5);
		else
			return (0);
		return (3);
	}
	return (0);
}

int		count(long int n)
{
	int			i;
	long int	nb;

	i = 0;
	nb = n;
	if (nb == 0)
		return (1);
	if (nb < 0)
		i++;
	while (nb != 0)
	{
		i++;
		nb = nb / 10;
	}
	return (i);
}
