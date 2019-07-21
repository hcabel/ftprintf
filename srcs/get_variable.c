/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 14:36:48 by hcabel            #+#    #+#             */
/*   Updated: 2019/07/20 15:12:54 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*cast_to_size(t_flags flags, void *arg, int base)
{
	if ((flags.type == 'd' || flags.type == 'i'))
		return (ft_baselen((long long)((int)arg), base));
	else if (flags.type == 'o')
		return (ft_baselen((unsigned int)arg, base));
	else if (flags.type == 'x' || flags.type == 'X')
		return (ft_baselen((unsigned int)arg, base));
	else if (flags.type == 'u')
		return (ft_baselen((unsigned int)arg, base));
	return (NULL);
}

static char	*cast_to_str(t_flags flags, void *arg, int base)
{
	if ((flags.type == 'd' || flags.type == 'i'))
		return (ft_itoa_base((long long)((int)arg), base));
	else if (flags.type == 'o')
		return (ft_itoa_base((unsigned int)arg, base));
	else if (flags.type == 'x' || flags.type == 'X')
		return (ft_itoa_base((unsigned int)arg, base));
	else if (flags.type == 'u')
		return (ft_itoa_base((unsigned int)arg, base));
	return (NULL);
}

int			get_size(void *arg, t_flags flags)
{
	if (flags.type == 'c')
		return (1);
	else if (flags.type == 's')
		return ((char*)arg == NULL ? -1 : ft_strlen((char*)arg));
	else if (flags.type == 'p')
		return (ft_baselen((unsigned long)arg, 16) + 2);
	else if (flags.type == 'd' || flags.type == 'i')
		if ((int)arg < 0)
			return (cast_to_size(flags, (unsigned int)arg, 10) - 1);
		else
			return (cast_to_size(flags, (unsigned int)arg, 10));
	else if (flags.type == 'o')
		return (cast_to_size(flags, (unsigned int)arg, 8));
	else if (flags.type == 'x' || flags.type == 'X')
		return (cast_to_size(flags, (unsigned int)arg, 16));
	else if (flags.type == 'u')
		return (cast_to_size(flags, (unsigned int)arg, 10));
}

char		*convert_to_char(void *arg, t_flags flags, int size, int *signe)
{
	char	*str;

	if (flags.type != 'x' || flags.type != 'X' || flags.type != 's')
		if (!(str = (char*)malloc(sizeof(char) * size)))
			return (NULL);
	if (flags.type == 'c')
		str[0] = (char)arg;
	else if (flags.type == 's')
	{
		if (str != NULL)
			str = (char*)arg;
	}
	else if (flags.type == 'p')
		str = ft_itoa_base((unsigned long)arg, 16);
	else if (flags.type == 'd' || flags.type == 'i')
		str = cast_to_str(flags, arg, 10);
	else if (flags.type == 'o')
		str = cast_to_str(flags, arg, 8);
	else if (flags.type == 'x' || flags.type == 'X')
		str = cast_to_str(flags, arg, 16);
	else if (flags.type == 'u')
		str = cast_to_str(flags, arg, 10);
	*signe = (str[0] == '-' ? 1 : 0);
	return (str);
}
