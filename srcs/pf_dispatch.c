/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_dispatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 13:25:27 by hcabel            #+#    #+#             */
/*   Updated: 2019/08/02 13:07:30 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	pf_display_flags(va_list args, char *str, int *ret)
{
	t_flags	flags;
	int 	i;
	double	tmp;
	void	*void_ptr;

	i = pf_parse_flags(&flags, str);
	if (!(ft_strchr("%diouxXcspf", flags.type)))
		return (i);
	if (flags.type == 'f')
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
	if (str[0] == '%')
		return (pf_display_flags(args, str + 1, ret));
	return (0);
}
