/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_dispatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylewis <sylewis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 13:25:27 by hcabel            #+#    #+#             */
/*   Updated: 2019/10/11 15:04:14 by sylewis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int			add_hashtag(char *str_arg, t_flags flags, t_newvalues *nv, int i)
{
	if ((flags.type == 'x' && IS_HASHTAG && str_arg[0] != '0')
		|| flags.type == 'p')
		i += ADDTOSTR("0x");
	else if (flags.type == 'o' && IS_HASHTAG && str_arg[0] != '0')
		i += ADDTOSTR("0");
	else if (flags.type == 'X' && IS_HASHTAG && str_arg[0] != '0')
		i += ADDTOSTR("0X");
	return (i);
}

static int	pf_display_flags(va_list args, char *str, int *ret)
{
	t_flags		flags;
	int			i;
	double		tmp;
	long double	long_tmp;
	void		*void_ptr;

	i = pf_parse_flags(&flags, str);
	if (flags.type == '\0')
		return (i - 1);
	if (!(ft_strchr("%diouxXcspf", flags.type)))
		return (i - 1);
	if (flags.type == 'f' && flags.scale[0] == 'L')
	{
		long_tmp = va_arg(args, long double);
		void_ptr = &long_tmp;
	}
	else if (flags.type == 'f')
	{
		tmp = va_arg(args, double);
		void_ptr = &tmp;
	}
	else
		void_ptr = (void*)va_arg(args, void*);
	*ret += pf_modify_value(void_ptr, flags);
	return (i);
}

int			pf_dispatch(va_list args, char *str, int *ret)
{
	if (str[0] == '{' && ft_strchr("rgybmc/", str[1]))
		return (colour_parse(str));
	else if ((str[0] == '%' && str[1] == '{')
		|| (str[0] == '{' && !ft_strchr("rgybmc/", str[1])))
	{
		write(1, &"{", 1);
		if (str[0] == '%' && str[1] == '{')
			return (2);
		return (1);
	}
	else if (str[0] == '%' && str[1] != '{')
		return (pf_display_flags(args, str + 1, ret));
	return (1);
}
