/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 13:46:47 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/07 10:19:48 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	display(t_flags *lst_flags, t_variable *lst_variable
			, t_constchar *lst_constchar)
{
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
				show_c(lst_variable->content, lst_flags);
			else if (lst_flags->type == 's')
				show_s(lst_variable->content, lst_flags);
			else if (lst_flags->type == 'p')
				ft_putchar(lst_flags->type);
			else if (lst_flags->type == 'd' || lst_flags->type == 'i')
				ft_putchar(lst_flags->type);
			else if (lst_flags->type == 'o')
				ft_putchar(lst_flags->type);
			else if (lst_flags->type == 'x')
				ft_putchar(lst_flags->type);
			else if (lst_flags->type == 'X')
				ft_putchar(lst_flags->type);
			else if (lst_flags->type == 'u')
				ft_putchar(lst_flags->type);
			else
				ft_putstr("{ERROR}");
			lst_variable = lst_variable->next;
			lst_flags = lst_flags->next;
		}
		if (lst_flags && !lst_variable)
			ft_putstr("{More variables please}");
	}
}
