/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 19:39:39 by hcabel            #+#    #+#             */
/*   Updated: 2019/07/09 00:37:57 by hcabel           ###   ########.fr       */
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

static int	pf_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '%' || (str[i] == '%' && str[i + 1] == '%')
		|| (str[i] == '%' && str[i - 1] == '%'))
		i++;
	write(1, str, i);
	return (i);
}

int			ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;

	va_start(args, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] != '%' && format[i - 1] != '%')
			i += pf_display(va_arg(args, void*), format + i);
		else
			i += pf_putstr(format + i);
	}
	va_end(args);
	return (0);
}