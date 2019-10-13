/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 13:28:32 by hcabel            #+#    #+#             */
/*   Updated: 2019/10/13 17:11:57 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_options(t_flags *flags, char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == '-' || str[i] == '+' || str[i] == '#'
		|| str[i] == '0' || str[i] == ' '))
	{
		if (str[i] == '-')
			flags->options[0] = '-';
		else if (str[i] == '+')
			flags->options[1] = '+';
		else if (str[i] == '#')
			flags->options[2] = '#';
		else if (str[i] == '0')
			flags->options[3] = '0';
		else if (str[i] == ' ')
			flags->options[4] = ' ';
		i++;
	}
	return (i);
}

static int	check_length(t_flags *flags, char *str)
{
	int	i;

	i = 0;
	flags->length = (str[i] >= '0' && str[i] <= '9' ? 0 : -1);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		flags->length = flags->length * 10 + str[i] - '0';
		i++;
	}
	return (i);
}

static int	check_precis(t_flags *flags, char *str)
{
	int	i;

	i = 0;
	flags->precis = -1;
	if (!str[i] || str[i] != '.')
		return (0);
	flags->precis = 0;
	while (str[i] && str[i] == '.')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		flags->precis = flags->precis * 10 + str[i] - '0';
		i++;
	}
	return (i);
}

static int	check_scale(t_flags *flags, char *str)
{
	if (str[0] == 'h')
	{
		flags->scale[0] = 'h';
		if (str[1] == 'h')
		{
			flags->scale[1] = 'h';
			return (2);
		}
		return (1);
	}
	else if (str[0] == 'l' || str[0] == 'L')
	{
		flags->scale[0] = str[0];
		if (str[1] == 'l')
		{
			flags->scale[1] = 'l';
			return (2);
		}
		return (1);
	}
	return (0);
}

int			pf_parse_flags(t_flags *flags, char *str)
{
	int		i;
	int		tmp;

	ft_bzero(flags->options, 5);
	ft_bzero(flags->scale, 2);
	i = 0;
	i += check_options(flags, str);
	i += check_length(flags, str + i);
	i += check_precis(flags, str + i);
	i += check_scale(flags, str + i);
	tmp = 0;
	while (str[i] && !ft_strchr("%diouxXcspf", str[i]))
		i++;
	if (str[i])
		flags->type = str[i++];
	else
		return (1);
	if (flags->type == 'f' && flags->precis == -1)
		flags->precis = 6;
	return (i + 1);
}
