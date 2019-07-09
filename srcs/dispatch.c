/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylewis <sylewis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 00:04:11 by hcabel            #+#    #+#             */
/*   Updated: 2019/07/09 23:52:51 by sylewis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	setup_func(t_func *func_adr[7])
{
	t_func *func;

	func = *func_adr;
	//func[0].f = show_c;
	func[0].type = 'c';
	//func[1].f = show_s;
	func[1].type = 's';
	//func[2].f = show_p;
	func[2].type = 'p';
	//func[3].f = show_d;
	func[3].type = 'd';
	//func[4].f = show_o;
	func[4].type = 'o';
	//func[5].f = show_x;
	func[5].type = 'x';
	//func[6].f = show_u;
	func[6].type = 'u';
}

static int	cal_size(void *arg, char type)
{
	if (type == 'c')
		return (1);
	else if (type == 's')
		return (ft_strlen((char*)arg));
	else if (type == 'p')
		return (1);
	else if (type == 'd' || type == 'i')
		return (ft_nbrlen(arg));
	else if (type == 'o')
		return (1);
	else if (type == 'x' || type == 'X')
		return (ft_baselen(arg, 16));
	else if (type == 'u')
		return (ft_nbrlen((char*)arg));
}

static char *convert_to_char(void *arg, char type, int size)
{
	int		i;
	char	*str;
	char	*string_arg;

	if (type != 'x' || type != 'X')
		if (!(str = (char*)malloc(sizeof(char) * size)))
			return (NULL);
	if (type == 'c')
		str[0] = (char)arg;
	else if (type == 's')
	{
		i = 0;
		string_arg = (char*)arg;
		while (string_arg[i])
			str[i - 1] = string_arg[i++];
	}
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
	return (str);
}

void		pf_dispatch(t_flags flags, void *arg)
{
	t_func	func[7];
	int		size;
	char	*str_arg;

	//setup_func(&func);
	size = cal_size(arg, flags.type);
	str_arg = convert_to_char(arg, flags.type, size);
	ft_putstr(str_arg);
}