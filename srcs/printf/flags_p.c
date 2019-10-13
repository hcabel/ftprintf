/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:11:50 by hcabel            #+#    #+#             */
/*   Updated: 2019/10/13 12:38:17 by hcabel           ###   ########.fr       */
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
}

static int	create_str(t_newvalues *nv)
{
	nv->str_size = ZERO_SIZE + SPACE_SIZE + nv->arg_size;
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
	i += ADDTOSTR("0x");
	i += fill(nv->zero_size, '0', &(nv->new_str), i);
	i += add_to_str(c, &(nv->new_str), i, nv->arg_size);
	if (IS_MINUS)
		i += fill(nv->space_size, ' ', &nv->new_str, i);
	return (0);
}

int		flags_p(void *arg, t_flags flags)
{
	t_newvalues	nv;
	char		*c;


	c = ft_utoa_base((unsigned long)arg, 16, 'a');
	nv.zero_size = 0;
	nv.is_negative = 0;
	nv.space_size = 0;
	if (c[0] == '0' && flags.precis == 0)
		nv.arg_size = 2;
	else
		nv.arg_size = ft_baselen((unsigned long)c, 16) + 2;
	set_additional_size(flags, &nv);
	if (create_str(&nv))
		return (-1);
	fill_str(c, flags, &nv);
	if (ft_strlen(nv.new_str) != 0)
		write(1, nv.new_str, nv.str_size);
	free(c);
	free(nv.new_str);
	return (nv.str_size);
}
