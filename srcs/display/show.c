/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 13:35:56 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/07 11:04:26 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	show_c(void *arg, t_flags *lst_flags)
{
	if (!find(lst_flags->options, '-'))
	{
		fill(' ', lst_flags->lenght_min - 1);
		ft_putchar((char)arg);
	}
	else
	{
		ft_putchar((char)arg);
		fill(' ', lst_flags->lenght_min - 1);
	}
}

void	show_s(void *arg, t_flags *lst_flags)
{
	int	size;
	int fill_size;

	size = 6;
	if (arg != NULL)
		size = ft_strlen((char*)arg);
	if (lst_flags->precis > -1 && lst_flags->precis < size)
		size = lst_flags->precis;
	fill_size = 0;
	if (lst_flags->lenght_min != -1)
		fill_size = lst_flags->lenght_min - size;
	if (!find(lst_flags->options, '-'))
	{
		fill(' ', fill_size);
		putnstr((char*)arg, size);
	}
	else
	{
		putnstr((char*)arg, size);
		fill(' ', fill_size);
	}
}
