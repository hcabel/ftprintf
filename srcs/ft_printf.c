/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 13:23:03 by hcabel            #+#    #+#             */
/*   Updated: 2019/08/15 20:52:13 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

static int	pf_putstr(char *str, int i, int *ret)
{
	int	j;

	j = 0;
	while (str[i + j] && str[i + j] != '%')
	{
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
		if (str[i] == '%')
			i += pf_dispatch(args, str + i, &ret);
		else
			i += pf_putstr(str, i, &ret);
	}
	va_end(args);
	return (ret);
}
