/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_dispatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylewis <sylewis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 13:25:27 by hcabel            #+#    #+#             */
/*   Updated: 2019/09/05 12:37:15 by sylewis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

static void	float_arg(va_list args, void **void_ptr_addr, t_flags flags)
{
	long double	tmp;
	double		tmp2;
	void		*void_ptr;

	void_ptr = *void_ptr_addr;
	if (flags.scale[0] == 'L')
	{
		tmp = va_arg(args, long double);
		void_ptr = &tmp;
	}
	else
	{
		tmp2 = va_arg(args, double);
		void_ptr = &tmp2;
	}
}

static int	pf_display_flags(va_list args, char *str, int *ret)
{
	t_flags		flags;
	int			i;
	
	void		*void_ptr;

	i = pf_parse_flags(&flags, str);
	if (!(ft_strchr("%diouxXcspf", flags.type)))
		return (i);
	if (flags.type == 'f')
	{
		float_arg(args, void_ptr, flags);
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
