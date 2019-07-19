/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 00:04:11 by hcabel            #+#    #+#             */
/*   Updated: 2019/07/19 14:25:26 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_size(void *arg, char type)
{
	if (type == 'c')
		return (1);
	else if (type == 's')
		return ((char*)arg == NULL ? -1 : ft_strlen((char*)arg));
	else if (type == 'p')
		return (ft_baselen((unsigned long)arg, 16) + 2);
	else if (type == 'd' || type == 'i')
		if ((int)arg < 0)
			return (ft_nbrlen((int)arg) - 1);
		else
			return (ft_nbrlen((int)arg));
	else if (type == 'o')
		return (ft_baselen((unsigned int)arg, 8));
	else if (type == 'x' || type == 'X')
		return (ft_baselen((unsigned int)arg, 16));
	else if (type == 'u')
		return (ft_nbrlen((unsigned int)arg));
}

static char *convert_to_char(void *arg, char type, int size, int *signe)
{
	char	*str;
	int		sign;

	sign = -1;
	if (type != 'x' || type != 'X' || type != 's')
		if (!(str = (char*)malloc(sizeof(char) * size)))
			return (NULL);
	if (type == 'c')
		str[0] = (char)arg;
	else if (type == 's')
	{
		if (str != NULL)
			str = (char*)arg;
	}
	else if (type == 'p')
		str = ft_itoa_base((unsigned long)arg, 16);
	else if ((type == 'd' || type == 'i') && (int)arg < 0)
		str = ft_itoa((long long)((int)arg) * sign++);
	else if (type == 'd' || type == 'i')
		str = ft_itoa((int)arg);
	else if (type == 'o')
		str = ft_itoa_base((unsigned int)arg, 8);
	else if (type == 'x' || type == 'X')
		str = ft_itoa_base((unsigned int)arg, 16);
	else if (type == 'u')
		str = ft_itoa((unsigned int)arg);
	*signe = (sign == 0 ? 1 : 0);
	return (str);
}



void		calc_size(int *zero_si, int *space_si, int *str_si, t_flags flags)
{
	if (!(flags.precis == -1 && flags.length != -1))
	{
		if (flags.precis > *str_si && flags.type != 's')
			*zero_si = flags.precis - *str_si;
		else if (flags.precis != -1 && flags.precis < *str_si && flags.type == 's')
			*str_si = flags.precis;
		if (flags.type == 'o' && flags.options[2])
			*zero_si -= 1;
		if (flags.length != -1)
			if (flags.length > *zero_si + *str_si)
				*space_si = flags.length - (*zero_si + *str_si);
	}
	else
		if (flags.length > *str_si)
			*space_si = flags.length - *str_si;
	if ((flags.options[2] && flags.type == 'o')
		|| (flags.options[1] && (flags.type == 'd' || flags.type == 'i')))
		*space_si -= 1;
	else if (flags.options[2] && (flags.type == 'x' || flags.type == 'X'))
		*space_si -= 2;
	if (flags.options[3] && flags.type != 's')
	{
		if (flags.precis != -1)
			while ((*zero_si += 1) + *str_si < flags.precis)
				*space_si -= 1;
		else
			*zero_si += *space_si + 1;
		*space_si = (flags.precis != -1 ? *space_si : 0);
		*zero_si -= 1;
	}
}

void		pf_dispatch(t_flags flags, void *arg)
{
	int		str_size;
	int		zero_size;
	int		space_size;
	char	*str_arg;
	int		sign;

	if ((str_size = get_size(arg, flags.type)) != -1)
		str_arg = convert_to_char(arg, flags.type, str_size, &sign);
	str_arg = (str_size == -1 ? "(null)" : str_arg);
	str_size = (str_size == -1 ? 6 : str_size);
	zero_size = 0;
	if (flags.type == 'X')
		while (str_arg[zero_size])
			if (str_arg[zero_size] >= 'a' && str_arg[zero_size] <= 'z')
				str_arg[zero_size++] -= 32;
			else
				zero_size++;
	space_size = 0;
	zero_size = 0;
	calc_size(&zero_size, &space_size, &str_size, flags);
	if ((flags.options[4] && !sign && flags.options[1]) || (sign && !flags.options[1]))
		if (flags.options[3] && flags.precis == -1)
			zero_size--;
		else
			space_size--;
	if (!flags.options[0])
		fill(space_size, ' ');
	if (flags.type == 'p' || (flags.options[2]
		&& ((unsigned int)arg != 0 || flags.precis == 0)))
		if (flags.type == 'o')
			zero_size = (zero_size < 0 ? 1 : zero_size + 1);
		else if (flags.type == 'p' || (unsigned int)arg != 0)
			if (flags.type == 'X')
				write(1, &"0X", 2);
			else
				write(1, &"0x", 2);
	if (flags.options[1] && (int)arg >= 0)
		write(1, &"+", 1);
	else if (flags.options[4] && !sign)
		write(1, &" ", 1);
	if (sign && flags.type != 'u')
		write(1, &"-", 1);
	if (flags.type != 's' || flags.type != 'c')
		fill(zero_size, '0');
	if (flags.precis == 0 && (unsigned int)arg == 0)
		str_size = 0;
	write(1, str_arg, str_size);
	if (flags.options[0])
		fill(space_size, ' ');
}
