/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 14:36:48 by hcabel            #+#    #+#             */
/*   Updated: 2019/07/30 19:32:02 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static char	*cast_to_str(t_flags flags, void *arg)
{
	if ((flags.type == 'd' || flags.type == 'i'))
		if (flags.scale[0] == 'l')
			return (ft_itoa_base((long long)((long)arg), 10));
		else
			return (ft_itoa_base((long long)((int)arg), 10));
	else if (flags.type == 'o')
		if (flags.scale[0] == 'l')
			return (ft_utoa_base((unsigned long)arg, 8, 'a'));
		else
			return (ft_utoa_base((unsigned int)arg, 8, 'a'));
	else if (flags.type == 'x')
		if (flags.scale[0] == 'l')
			return (ft_utoa_base((unsigned long)arg, 16, 'a'));
		else
			return (ft_utoa_base((unsigned int)arg, 16, 'a'));
	else if (flags.type == 'X')
		if (flags.scale[0] == 'l')
			return (ft_utoa_base((unsigned long)arg, 16, 'A'));
		else
			return (ft_utoa_base((unsigned int)arg, 16, 'A'));
	else if (flags.type == 'u')
	{
		if (flags.scale[0] == 'l')
			return (ft_utoa_base((unsigned long)arg, 10, 'a'));
		else
			return (ft_utoa_base((unsigned int)arg, 10, 'a'));
	}
	else if (flags.type == 'f')
		return (ft_ftoa((double)arg));
	else
		return ("0");
}

char		*convert_to_char(void *arg, t_flags flags, int *sign)
{
	char	*str;

	*sign = 0;
	str = NULL;
	if (flags.type == 'c')
		if (!(str = (char*)malloc(sizeof(char) * 1)))
			return (NULL);
	if (flags.type == 'c')
		str[0] = (char)arg;
	else if (flags.type == 's')
	{
		if ((char*)arg != NULL)
			str = (char*)(arg);
	}
	else if (flags.type == 'p')
		str = ft_itoa_base((unsigned long)arg, 16);
	else
		str = cast_to_str(flags, arg);
	if ((flags.type != 'c' && flags.type != 's') && str[0] == '-')
		*sign = 1;
	return (str + *sign);
}
