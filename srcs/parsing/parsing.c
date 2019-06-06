/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 13:07:23 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/06 16:35:25 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			add_last(t_constchar **lst, t_constchar *elem)
{
	t_constchar *list;

	list = *lst;
	while (list->next != NULL)
		list = list->next;
	list->next = elem;
	elem->next = NULL;
}

static t_constchar	*init_lst(void *content)
{
	t_constchar	*new;

	if (!(new = (t_constchar*)malloc(sizeof(t_constchar))))
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

static int			dispatch_format(const char *format, t_flags **lst_flags
						, t_constchar **lst_constchar)
{
	int	nb_args;
	int	i;
	int	i2;

	nb_args = 0;
	*lst_constchar = NULL;
	*lst_flags = NULL;
	i = 0;
	while (format[i])
	{
		i2 = 0;
		while ((format[i + i2] != '%' && format[i + i2] != '\0')
			|| (format[i + i2] == '%' && format[i + i2 + 1] == '%')
			|| (format[i + i2] == '%' && format[i + i2 - 1] == '%'))
			i2++;
		nb_args++;
		if (*lst_constchar == NULL)
			*lst_constchar = init_lst(ft_strndup(format + i, i2 - i));
		else
			add_last(lst_constchar, init_lst(ft_strndup(format + i, i2)));
		i = new_arg(lst_flags, format, i + i2);
	}
	return (nb_args - 1);
}

t_variable			*parsing(const char *format, t_flags **lst_flags
						, t_constchar **lst_constchar, va_list args)
{
	int	args_nb;

	args_nb = dispatch_format(format, lst_flags, lst_constchar);
	if (args_nb == -1)
		finish("Error parsing format");
	return (stock_variable(args_nb, args));
}
