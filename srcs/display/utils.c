/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 10:22:35 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/07 11:11:24 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fill(char chara, int size)
{
	int	i;

	i = 0;
	if (size < 0)
		return ;
	while (i++ < size)
		ft_putchar(chara);
}

int		find(char *str, char chara)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == chara)
			return (1);
		i++;
	}
	return (0);
}

void	putnstr(char *str, int size)
{
	int	scale;

	if (str == NULL)
	{
		write(1, &("(null)"), size);
		return ;
	}
	scale = ft_strlen(str);
	if (scale > size)
		write(1, str, size);
	else
		write(1, str, scale);
}
