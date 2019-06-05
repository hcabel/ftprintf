/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 14:48:12 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/04 14:18:14 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		add_last(t_variable **lst, t_variable *elem)
{
	t_variable *list;

	list = *lst;
	while (list->next != NULL)
		list = list->next;
	list->next = elem;
	elem->next = NULL;
}

static t_variable	*init_lst(void	*content)
{
	t_variable	*new;

	if (!(new = (t_variable*)malloc(sizeof(t_variable))))
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

t_variable			*stock_variable(int args_nb, va_list args)
{
	t_variable	*list;
	int			i;

	list = NULL;
	i = 0;
	while (i < args_nb)
	{	
		if (list == NULL)
			list = init_lst(va_arg(args, void*));
		else
			add_last(&list, init_lst(va_arg(args, void*)));
		i++;
	}
	return (list);
}