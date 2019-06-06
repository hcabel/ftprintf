/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 13:46:47 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/06 14:22:39 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*
void	init_tab(void (**f[8])(void*))
{
	
}*/

void	display(t_flags *lst_flags, t_variable *lst_variable
			, t_constchar *lst_constchar)
{
	void	(*f[4])(void*);
	t_variable	*lst;

	lst = lst_variable;
	f[0] = put_cast_char;
	f[1] = put_cast_str;
	while (lst_flags || lst_variable || lst_constchar)
	{
		if (lst_constchar)
		{
			ft_putstr(lst_constchar->content);
			lst_constchar = lst_constchar->next;
		}
		if (lst_variable && lst_flags)
		{
			if (lst_flags->type == 'c')
				f[0](lst_variable->content);
			else if (lst_flags->type == 's')
				f[1](lst_variable->content);
			else if (lst_flags->type == 'd')
				ft_putstr("{number}");
			else if (lst_flags->type == 'u')
				ft_putstr("{unsigned number}");
			lst_variable = lst_variable->next;
			lst_flags =	lst_flags->next;
		}
		else if (lst_flags && !lst_variable)
			ft_putstr("{More variables please}");
	}
	while (lst)
	{
	/*	put_cast_signed(lst->content);
		ft_putstr("\n");*/
		lst = lst->next;
	}
	
}