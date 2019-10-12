/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:11:50 by hcabel            #+#    #+#             */
/*   Updated: 2019/10/12 15:35:24 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

static void	set_additional_size(t_flags flags, t_newvalues *nv)
{
	if (flags.precis != -1 || flags.length == -1)
	{
		if (flags.precis > nv->arg_size)
			nv->zero_size = flags.precis - nv->arg_size;
		if (flags.length != -1)
			if (flags.length > nv->zero_size + nv->arg_size)
				nv->space_size = flags.length - (nv->zero_size + nv->arg_size);
	}
	else if (flags.length > 1)
		nv->space_size = flags.length - nv->arg_size;
	if (IS_NEGA)
		nv->space_size--;
	else if (IS_PLUS)
		nv->space_size--;
	else if (IS_SPACE)
		nv->space_size--;
	if (IS_0)
	{
		if (flags.precis != -1)
			while ((nv->zero_size += 1) + nv->arg_size < flags.precis)
				nv->space_size -= 1;
		else
			nv->zero_size += nv->space_size + 1;
		nv->space_size = (flags.precis != -1 ? nv->space_size : 0);
		nv->zero_size -= 1;
	}
}

static int	create_str(t_flags flags, t_newvalues *nv)
{
	nv->str_size = ZERO_SIZE + SPACE_SIZE + nv->arg_size;
	if (IS_NEGA)
		nv->str_size++;
	else if (IS_PLUS)
		nv->str_size++;
	else if (IS_SPACE)
		nv->str_size++;
	if (!(nv->new_str = (char*)malloc(sizeof(char) * nv->str_size)))
		return (1);
	return (0);
}

static int	fill_str(char *c, t_flags flags, t_newvalues *nv)
{
	int	i;

	i = 0;
	if (!IS_MINUS)
		i += fill(nv->space_size, ' ', &nv->new_str, i);
	if (IS_NEGA)
		i += ADDTOSTR("-");
	else if (IS_PLUS)
		i += ADDTOSTR("+");
	else if (IS_SPACE)
		i += ADDTOSTR(" ");
	i += fill(nv->zero_size, '0', &(nv->new_str), i);
	if (c[0] != '0' || flags.precis != 0)
		i += add_to_str(c + IS_NEGA, &(nv->new_str), i, nv->arg_size);
	if (IS_MINUS)
		i += fill(nv->space_size, ' ', &nv->new_str, i);
	return (0);
}

int		flags_d(void *arg, t_flags flags)
{
	t_newvalues	nv;
	char		*c;

	if (flags.scale[0] == 'l')
		c = ft_itoa_base((long long)((long)arg), 10);
	else if (flags.scale[1] == 'h')
		c = ft_itoa((signed char)arg);
	else if (flags.scale[0] == 'h')
		c = ft_itoa((short)arg);
	else
		c = ft_itoa_base((long long)((int)arg), 10);
	nv.zero_size = 0;
	nv.space_size = 0;
	nv.arg_size = ft_strlen(c);
	nv.is_negative = (*c == '-' ? 1 : 0);
	nv.arg_size -= (*c == '-' ? 1 : 0);
	set_additional_size(flags, &nv);
	if (create_str(flags, &nv))
		return (-1);
	fill_str(c, flags, &nv);
	write(1, nv.new_str, nv.str_size);
	return (nv.str_size);
}
