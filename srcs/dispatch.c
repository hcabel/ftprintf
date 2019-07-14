/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 00:04:11 by hcabel            #+#    #+#             */
/*   Updated: 2019/07/14 18:49:34 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	fill(int size, char c)
{
	char	*str;
	int		i;

	if (size < 0 || (str = (char*)malloc(sizeof(char) * size)) == NULL)
		return ;
	i = 0;
	while (i < size)
		str[i++] = c;
	write(1, str, size);
	free(str);
}

static int	cal_size(void *arg, char type)
{
	if (type == 'c')
		return (1);
	else if (type == 's')
		return ((char*)arg == NULL ? -1 : ft_strlen((char*)arg));
	else if (type == 'p')
		return (1);
	else if (type == 'd' || type == 'i')
		if ((int)arg < 0)
			return ((int)arg == NULL ? -1 : ft_nbrlen((int)arg) - 1);
		else
			return ((int)arg == NULL ? -1 : ft_nbrlen((int)arg));
	else if (type == 'o')
		return (ft_baselen((unsigned int)arg, 8));
	else if (type == 'x' || type == 'X')
		return (ft_baselen((unsigned int)arg, 16));
	else if (type == 'u')
		return ((int)arg == NULL ? -1 : ft_nbrlen(arg));
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
		str = (char*)arg;
	else if (type == 'p')
		str[0] = type;
	else if ((type == 'd' || type == 'i') && (int)arg < 0)
		str = ft_itoa(((int)arg) * sign++);
	else if (type == 'd' || type == 'i')
		str = ft_itoa((int)arg);
	else if (type == 'o')
		str = ft_itoa_base((unsigned int)arg, 8);
	else if (type == 'x' || type == 'X')
		str = ft_itoa_base((unsigned int)arg, 16);
	else if (type == 'u')
		str[0] = type;
	*signe = (sign == 0 ? 1 : 0);
	return (str);
}

void		calc_size(int *zero_si, int *space_si, int *str_si, t_flags flags)
{
	int	i;

	*space_si = 0;
	*zero_si = 0;
	if (flags.precis != -1 && flags.length != -1)
	{
		if (flags.precis > *str_si)
			*zero_si = flags.precis - *str_si;
		if (flags.type == 'o' && flags.options[2] == '#')
			*zero_si -= 1;
		if (flags.length > *zero_si + *str_si)
			*space_si = flags.length - (*zero_si + *str_si);
	}
	else if (flags.precis != -1  && flags.length == -1)
	{
		if (flags.precis > *str_si)
			*zero_si = flags.precis - *str_si;
		if (flags.type == 'o' && flags.options[2] == '#')
			*zero_si -= 1;
	}
	else if (flags.precis == -1 && flags.length != -1)
	{
		if (flags.length > *str_si)
			*space_si = flags.length - *str_si;
	}
	if (flags.options[3] == '0')
	{
		if (flags.precis != -1)
		{
			while (*zero_si < flags.precis)
			{
				*zero_si++;
				*space_si--;
			}
		}
		else
		{
			*zero_si += *space_si;
			*space_si = 0;
		}
	}
	if (flags.options[2] == '#')
		if (flags.type == 'x' || flags.type == 'X')
			*space_si -= 2;
		else if (flags.type == 'o')
			*space_si -= 1;
}

void		pf_dispatch(t_flags flags, void *arg)
{
	int		str_size;
	int		zero_size;
	int		space_size;
	char	*str_arg;
	int		sign;

	if ((str_size = cal_size(arg, flags.type)) != -1)
		str_arg = convert_to_char(arg, flags.type, str_size, &sign);
	else
	{
		str_arg = "(null)";
		str_size = 6;
	}
	if (flags.type == 'X')
	{
		zero_size = 0;
		while (str_arg[zero_size])
			if (str_arg[zero_size] >= 'a' && str_arg[zero_size] <= 'z')
				str_arg[zero_size++] -= 32;
			else
				zero_size++;
	}
	calc_size(&zero_size, &space_size, &str_size, flags);
	if (flags.options[0] != '-')
		fill(space_size, ' ');
	if (flags.options[2] == '#' && ((unsigned int)arg != 0 || flags.precis == 0))
		if (flags.type == 'o')
			zero_size = (zero_size < 0 ? 1 : zero_size + 1);
		else if ((unsigned int)arg != 0)
			if (flags.type == 'X')
				write(1, &"0X", 2);
			else
				write(1, &"0x", 2);
	if (flags.type != 's' || flags.type != 'c')
		fill(zero_size, '0');
	if (flags.precis == 0 && (unsigned int)arg == 0)
		str_size = 0;
	write(1, str_arg, str_size);
	if (flags.options[0] == '-')
		fill(space_size, ' ');
}
