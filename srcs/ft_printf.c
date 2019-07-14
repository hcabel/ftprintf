/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 19:39:39 by hcabel            #+#    #+#             */
/*   Updated: 2019/07/13 18:22:12 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		pf_error(char *reason)
{
	ft_putstr("{ ");
	ft_putstr(reason);
	ft_putstr(" }");
	exit(0);
}

static int	pf_putstr(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i + j])
	{
		if (str[i + j] == '%' && str[i + j - 1] != '%')
			break ;
		else
			j++;
	}
	write(1, str + i, j);
	return (j);
}

int			ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;

	va_start(args, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i - 1] != '%')
			i += pf_display(args, format + i);
		else
			i += pf_putstr(format, i);
	}
	va_end(args);
	return (0);
}