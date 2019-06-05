/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 13:46:47 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/05 16:03:48 by hcabel           ###   ########.fr       */
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
	void	(*f[8])(void*);

	f[0] = put_cast_char;
	f[1] = put_cast_str;
	f[2] = put_cast_int;
	f[3] = put_cast_unsigned_int;
	f[4] = put_cast_short;
	f[5] = put_cast_unsigned_short;
	f[6] = put_cast_long;
	f[7] = put_cast_unsigned_long;
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
			else if (lst_flags->type == 'd' || lst_flags->type == 'i')
			{
				if (lst_flags->scale[0] == 'l' && lst_flags->scale[1] == 'l')
					f[7](lst_variable->content);
				else if (lst_flags->scale[0] == 'h' && lst_flags->scale[1] == 'h')
					f[0](lst_variable->content);
				else if (lst_flags->scale[0] == 'h')
					f[3](lst_variable->content);
				else if (lst_flags->scale[0] == 'l')
					f[5](lst_variable->content);
				else
					f[2](lst_variable->content);
			}
			else if (lst_flags->type == 'u')
				f[3](lst_variable->content);
			lst_variable = lst_variable->next;
			lst_flags =	lst_flags->next;
		}
		else if (lst_flags && !lst_variable)
			ft_putstr("{More variables please}");
	}
}