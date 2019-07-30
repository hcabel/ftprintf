/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 19:39:39 by hcabel            #+#    #+#             */
/*   Updated: 2019/07/30 15:15:52 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

void		pf_error(char *reason)
{
	ft_putstr("{ ");
	ft_putstr(reason);
	ft_putstr(" }");
	//exit(0);
}

static int	pf_putstr(char *str, int i, int *ret)
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
	*ret += j;
	return (j);
}

int			ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		ret;
	char	*str;

	str = (char*)format;
	va_start(args, format);
	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i - 1] != '%')
			i += pf_display(args, str + i, &ret);
		else
			i += pf_putstr(str, i, &ret);
	}
	va_end(args);
	return (ret);
}
