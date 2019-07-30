/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 00:04:11 by hcabel            #+#    #+#             */
/*   Updated: 2019/07/30 17:38:15 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

void		add_flags(int *zero_si, int *space_si, int *str_si, t_flags flags)
{
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

static int		init_size(int *zero_si, int *str_si, t_flags flags, int sign)
{
	int	space_si;

	space_si = 0;
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
				space_si = flags.length - (*zero_si + *str_si);
	}
	else
		if (flags.length > *str_si)
			space_si = flags.length - *str_si;
	add_flags(zero_si, &space_si, str_si, flags);
	if ((flags.options[4] && !sign && flags.options[1]) || (sign && !flags.options[1]))
	{
		if (flags.options[3] && flags.precis == -1)
			*zero_si -= 1;
		else
			space_si -= 1;
	}
	return (space_si);
}

static char	*set_writing_str(void *arg, t_flags flg, int *arg_si, int *i)
{
	char	*str;
	int		add_si[3];
	char	*tmp;
	int		sign;

	tmp = convert_to_char(arg, flg, &sign);
	if (tmp == NULL && flg.type == 's')
	{
		tmp = "(null)";
		add_si[2] = 6;
	}
	else if (tmp != NULL)
		add_si[2] = ft_strlen(tmp);

	add_si[0] = 0;
	add_si[1] = init_size(&add_si[0], &add_si[2], flg, sign);

	*arg_si = (add_si[0] < 0 ? 0 : add_si[0])
		+ (add_si[1] < 0 ? 0 : add_si[1]) + (add_si[2]);
	if (flg.options[2] && ((unsigned int)arg != 0 || flg.precis == 0))
		*arg_si += 2;
	if (flg.options[1] && (int)arg >= 0)
		*arg_si += 1;
	else if (flg.options[4] && !sign)
		*arg_si += 1;
	if (sign)
		*arg_si += 1;
	if (!(str = (char*)malloc(sizeof(char) * (*arg_si)))) // calcul arg size
		return (0);
	ft_bzero(str, *arg_si); // verif

	*i = 0;
	if (!flg.options[0])
		*i += fill(add_si[1], ' ', &str, *i);
	if (flg.type == 'p' || (flg.options[2]
		&& ((unsigned int)arg != 0 || flg.precis == 0)))
	{
		if (flg.type == 'o')
			add_si[0] = (add_si[0] < 0 ? 1 : add_si[0] + 1);
		else if ((flg.type == 'p' || (unsigned int)arg != 0) && flg.type == 'X')
			*i += add("0X", &str, *i, *arg_si);
		else if ((flg.type == 'p' || (unsigned int)arg != 0))
			*i += add("0x", &str, *i, *arg_si);
	}
	*i += (flg.options[1] && (int)arg >= 0 ? add("+", &str, *i, *arg_si) : 0);
	*i += (flg.options[4] && !sign ? add(" ", &str, *i, *arg_si) : 0);
	*i += (sign && flg.type != 'u' ? add("-", &str, *i, *arg_si) : 0);
	if (flg.type != 's' && flg.type != 'c')
		*i += fill(add_si[0], '0', &str, *i);
	add_si[2] = (flg.precis == 0 && (unsigned int)arg == 0 ? 0 : add_si[2]);
	*i += add(tmp, &str, *i, add_si[2]);
	if (flg.options[0])
		*i += fill(add_si[1], ' ', &str, *i);
	return (str);
}

int			pf_dispatch(t_flags flags, void *arg)
{
	int		i;
	int		arg_size;
	char	*str_arg;

	str_arg = set_writing_str(arg, flags, &arg_size, &i);

	write(1, str_arg, arg_size);
	free(str_arg);
	return (i);
}
