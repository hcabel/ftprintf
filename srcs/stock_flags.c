/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 14:48:12 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/05 09:41:42 by hcabel           ###   ########.fr       */
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
	new->options = "\0";
	new->lenght_min = 0;
	new->precis = "\0";
	new->scale = 0;
	new->type = '\0';
	new->next = NULL;
	return (new);
}

int				new_arg(t_flags **lst_flags, const char *str, int i)
{/*
	t_flags *flags_ptr;
	int	i2;

	flags_ptr = *lst_flags;
	if (*lst_flags == NULL)
		*lst_flags = init_lst();
	else
		add_last(lst_flags, init_lst());
	i2 = 1;
	i++;
	while (str[i] == '-' || str[i] == '+' || str[i] == '#' || str[i] == '0' || str[i] == ' ')
	{
		flags_ptr->options[i2] = str[i];
		i++;
		i2++;
	}
	if (ft_isdigit(str[i]))
	{
		flags_ptr->lenght_min = ft_atoi(str + i);
		while (ft_isdigit(str[i]))
		{
			i++;
			i2++;
		}
	}
	if (str[i] == '.' && ft_isdigit(str[i + 1]))
	{
		i++;
		i2++;
		flags_ptr->scale = ft_atoi(str + i);
		while (ft_isdigit(str[i]))
		{
			i++;
			i2++;
		}
	}
	flags_ptr->type = str[i];
	return (i2);*/
}