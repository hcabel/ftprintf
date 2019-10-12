/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_dispatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 13:25:27 by hcabel            #+#    #+#             */
/*   Updated: 2019/10/12 15:26:19 by hcabel           ###   ########.fr       */
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

static int	pf_select_flags(va_list args, char *str, int *ret)
{
	t_flags		flags;
	int			i;
	void		*void_ptr;

	i = pf_parse_flags(&flags, str);
	if (flags.type == '\0' || !(ft_strchr("%diouxXcspf", flags.type)))
		return (i - 1);
	void_ptr = (void*)va_arg(args, void*);
	if (flags.type == 'c')
		*ret += flags_c(void_ptr, flags);
	else if (flags.type == 's')
		*ret += flags_s(void_ptr, flags);
	else if (flags.type == 'p')
		*ret += flags_p(void_ptr, flags);
	else if (flags.type == 'd' || flags.type == 'i')
		*ret += flags_d(void_ptr, flags);
	else if (flags.type == 'o')
		*ret += flags_o(void_ptr, flags);
	return (i);
}

int			pf_dispatch(va_list args, char *str, int *ret)
{
	if (str[0] == '{' && ft_strchr("rgybmc/", str[1]))
		return (colour_parse(str));
	else if (str[0] == '%' && str[1] != '{')
		return (pf_select_flags(args, str + 1, ret));
	return (1);
}
