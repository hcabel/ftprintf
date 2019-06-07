/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 14:48:12 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/07 10:46:10 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		add_last(t_flags **lst, t_flags *elem)
{
	t_flags *list;

	list = *lst;
	while (list->next != NULL)
		list = list->next;
	list->next = elem;
	elem->next = NULL;
}

static t_flags	*init_lst(void)
{
	t_flags	*new;

	if (!(new = (t_flags*)malloc(sizeof(t_flags))))
		return (NULL);
	new->options = ft_strnew(0);
	new->lenght_min = -1;
	new->precis = -1;
	new->scale = ft_strnew(0);
	new->type = '\0';
	new->next = NULL;
	return (new);
}

static int		scale(t_flags *flags_ptr, const char *str, int i)
{
	if (str[i] == 'h')
	{
		flags_ptr->scale[0] = 'h';
		if (str[++i] == 'h')
		{
			flags_ptr->scale[1] = 'h';
			i++;
		}
	}
	else if (str[i] == 'l')
	{
		flags_ptr->scale[0] = 'l';
		if (str[++i] == 'l')
		{
			flags_ptr->scale[1] = 'l';
			i++;
		}
	}
	return (i);
}

static int		option_lenght_precis(t_flags *flags_ptr, const char *str, int i)
{
	int i2;

	i2 = 0;
	while (str[i] == '-' || str[i] == '+' || str[i] == '#'
		|| str[i] == '0' || str[i] == ' ')
	{
		flags_ptr->options[i2] = str[i];
		i++;
		i2++;
	}
	if (ft_isdigit(str[i]))
	{
		flags_ptr->lenght_min = ft_atoi(str + i);
		while (ft_isdigit(str[i]))
			i++;
	}
	if (str[i] == '.' && ft_isdigit(str[i + 1]))
	{
		i++;
		flags_ptr->precis = ft_atoi(str + i);
		while (ft_isdigit(str[i]))
			i++;
	}
	return (i);
}

int				new_arg(t_flags **lst_flags, const char *str, int i)
{
	t_flags	*flags_ptr;

	if (str[i] != '%')
		return (i);
	if (*lst_flags == NULL)
		*lst_flags = init_lst();
	else
		add_last(lst_flags, init_lst());
	flags_ptr = *lst_flags;
	while (flags_ptr->next)
		flags_ptr = flags_ptr->next;
	i++;
	i = option_lenght_precis(flags_ptr, str, i);
	i = scale(flags_ptr, str, i);
	flags_ptr->type = str[i];
	return (i + 1);
}
