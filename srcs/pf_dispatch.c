/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_dispatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 13:25:27 by hcabel            #+#    #+#             */
/*   Updated: 2019/08/02 01:14:22 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	pf_display_flags(va_list args, char *str, int *ret)
{
	t_flags	flags;
	int 	i;

	i = pf_parse_flags(&flags, str);
	if (!(ft_strchr("%diouxXcsp", flags.type)))
		return (i);
	*ret += pf_modify_value(va_arg(args, void*), flags);
	return (i);
}

int			pf_dispatch(va_list args, char *str, int *ret)
{
	if (str[0] == '%')
		return (pf_display_flags(args, str + 1, ret));
	return (0);
}
