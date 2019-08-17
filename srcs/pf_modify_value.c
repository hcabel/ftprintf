/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_modify_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 13:33:03 by hcabel            #+#    #+#             */
/*   Updated: 2019/08/15 20:55:16 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

static void add_flags(t_flags flags, t_newvalues *nv)
{
	if ((IS_PLUS && !nv->is_negative) || (flags.type == 'o' && IS_HASHTAG))
		nv->space_size--;
	else if (nv->is_negative)
		nv->space_size--;
	if (IS_SPACE && !IS_PLUS && !nv->is_negative)
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
	if ((flags.type == 'x' || flags.type == 'X') && IS_HASHTAG)
		nv->space_size -= 2;
}

static void	set_additional_size(t_flags flags, t_newvalues *nv)
{
	if (!(flags.precis == -1 && flags.length != -1))
	{
		if (flags.precis > nv->arg_size && flags.type != 's')
			nv->zero_size = flags.precis - nv->arg_size;
		else if (flags.precis != -1 && flags.precis < nv->arg_size
			&& flags.type == 's')
			nv->arg_size = flags.precis;
		if (flags.type == 'o' && IS_HASHTAG)
			nv->zero_size -= 1;
		if (flags.length != -1)
			if (flags.length > nv->zero_size + nv->arg_size)
				nv->space_size = flags.length - (nv->zero_size + nv->arg_size);
	}
	else
		if (flags.length > nv->arg_size)
			nv->space_size = flags.length - nv->arg_size;
	add_flags(flags, nv);
}

static void	create_new_str(t_flags flags, t_newvalues *nv)
{
	nv->str_size = ZERO_SIZE + SPACE_SIZE + nv->arg_size;
	if (IS_HASHTAG)
		nv->str_size += 2;
	if (nv->is_negative || IS_PLUS)
		nv->str_size++;
	else if (IS_SPACE)
		nv->str_size++;
	if (!(nv->new_str = (char*)malloc(sizeof(char) * (nv->str_size))))
		return ;
	ft_bzero(nv->new_str, nv->str_size + 2);
}

static void	create_new_arg(char *str_arg, t_flags flags, t_newvalues *nv)
{
	int	i;

	set_additional_size(flags, nv);
	create_new_str(flags, nv);
	i = 0;
	if (!IS_MINUS)
		i += fill(nv->space_size, ' ', &nv->new_str, i);
	if ((flags.type == 'x' && IS_HASHTAG && str_arg[0] != '0')
		|| flags.type == 'p')
		i += ADDTOSTR("0x");
	else if (flags.type == 'o' && IS_HASHTAG)
		i += ADDTOSTR("0");
	else if (flags.type == 'X' && IS_HASHTAG && str_arg[0] != '0')
		i += ADDTOSTR("0X");
	else if (IS_PLUS && !nv->is_negative)
		i += ADDTOSTR("+");
	else if (IS_SPACE && !IS_PLUS && !nv->is_negative)
		i += ADDTOSTR(" ");
	else if (nv->is_negative && flags.type != 'u')
		i += ADDTOSTR("-");
	if (flags.type != 's' && flags.type != 'c')
		i += fill(nv->zero_size, '0', &(nv->new_str), i);
	i += add_to_str(str_arg, &(nv->new_str), i, nv->arg_size);
	if (IS_MINUS)
		i += fill(nv->space_size, ' ', &(nv->new_str), i);
}

int			pf_modify_value(void *arg, t_flags flags)
{
	t_newvalues	nv;
	char		*old_arg_str;

	nv.space_size = 0;
	nv.zero_size = 0;
	nv.is_negative = 0;
	if ((old_arg_str = convert_to_char(arg, flags, &nv)) == NULL)
		return (0);
	nv.arg_size = ft_strlen(old_arg_str);
	if (flags.type == 'p')
		nv.arg_size += 2;
	else if (flags.type == 'c' && old_arg_str[0] == '\0')
		nv.arg_size = 1;
	if (flags.precis == 0 && (int)arg == 0)
		nv.arg_size = 0;
	create_new_arg(old_arg_str, flags, &nv);
	write(1, nv.new_str, nv.str_size);
	if (flags.type == 'c')
		free(old_arg_str);
	free(nv.new_str);
	return (nv.str_size);
}
