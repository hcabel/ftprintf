/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylewis <sylewis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 00:04:11 by hcabel            #+#    #+#             */
/*   Updated: 2019/07/10 00:37:52 by sylewis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	cal_size(void *arg, char type)
{
	if (type == 'c')
		return (1);
	else if (type == 's')
		return ((char*)arg == NULL ? -1 : ft_strlen((char*)arg));
	else if (type == 'p')
		return (1);
	else if (type == 'd' || type == 'i')
		return ((int)arg == NULL ? -1 : ft_nbrlen(arg));
	else if (type == 'o')
		return (1);
	else if (type == 'x' || type == 'X')
		return ((int)arg == NULL ? -1 : ft_baselen(arg, 16));
	else if (type == 'u')
		return ((int)arg == NULL ? -1 : ft_nbrlen(arg));
}

static char *convert_to_char(void *arg, char type, int size)
{
	char	*str;

	if (type != 'x' || type != 'X' || type != 's')
		if (!(str = (char*)malloc(sizeof(char) * size)))
			return (NULL);
	if (type == 'c')
		str[0] = (char)arg;
	else if (type == 's')
		str = (char*)arg;
	else if (type == 'p')
		str[0] = type;
	else if (type == 'd' || type == 'i')
		str = ft_itoa((int) arg);
	else if (type == 'o')
		str = ft_itoa_base(arg, 8);
	else if (type == 'x' || type == 'X')
		str = ft_itoa_base(arg, 16);
	else if (type == 'u')
		str[0] = type;
	return (str != NULL ? str : NULL);
}

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

void		pf_dispatch(t_flags flags, void *arg)
{
	int		size;
	char	*str_arg;

	if ((size = cal_size(arg, flags.type)) != -1)
		str_arg = convert_to_char(arg, flags.type, size);
	else
	{
		str_arg = "(null)";
		size = 6;
	}
	size = (size > flags.precis && flags.precis != -1 ? flags.precis : size);
	if (flags.options[0] != '-')
		fill(flags.length - size, ' ');
	write(1, str_arg, size);
	if (flags.options[0] == '-')
		fill(flags.length - size, ' ');
}