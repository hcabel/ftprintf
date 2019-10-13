/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylewis <sylewis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:11:50 by hcabel            #+#    #+#             */
/*   Updated: 2019/10/13 16:46:16 by sylewis          ###   ########.fr       */
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

static int	create_str(char *c, t_flags flags, t_newvalues *nv)
{
	nv->str_size = ZERO_SIZE + SPACE_SIZE + nv->arg_size;
	if (IS_HASHTAG && !ft_strchr(c, '.'))
		nv->str_size += 1;
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
	if (IS_HASHTAG && !ft_strchr(c, '.'))
		i += ADDTOSTR(".");
	return (0);
}

int		flags_f(void *arg, t_flags flags)
{
	t_newvalues	nv;
	char		*c;

	if (flags.scale[0] == 'L')
		c = (ft_ftoa(*(long double*)arg, (flags.precis == -1 ? 6 : flags.precis)));
	else
		c = (ft_ftoa(*(double*)arg, (flags.precis == -1 ? 6 : flags.precis)));
    nv.zero_size = 0;
	nv.space_size = 0;
	nv.arg_size = ft_strlen(c);
	nv.is_negative = (*c == '-' ? 1 : 0);
	nv.arg_size -= (*c == '-' ? 1 : 0);
	if (*(double*)arg != 0 && flags.precis == 0)
		flags.precis++;
	set_additional_size(flags, &nv);
	if (create_str(c, flags, &nv))
		return (-1);
	fill_str(c, flags, &nv);
	if (ft_strlen(nv.new_str) != 0)
		write(1, nv.new_str, nv.str_size);
	free(c);
	free(nv.new_str);
	return (nv.str_size);
}
