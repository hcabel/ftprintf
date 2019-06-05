/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 14:00:17 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/05 14:12:57 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			finish(char *reason)
{
	ft_putstr("{ ft_printf error : ");
	ft_putstr(reason);
	ft_putendl(" }");
	exit(0);
}

int				ft_printf(const char *format, ...)
{
	t_variable	*lst_valeur;
	t_constchar	*lst_constchar;
	t_flags		*lst_flags;
	va_list		args;

	va_start(args, format);
	lst_valeur = parsing(format, &lst_flags, &lst_constchar, args);
	va_end(args);
	display(lst_flags, lst_valeur, lst_constchar);
	return (0);
}
