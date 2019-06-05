/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 14:00:17 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/05 10:11:49 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		finish(char *reason)
{
	ft_putstr("{ ft_printf error : ");
	ft_putstr(reason);
	ft_putendl(" }");
	exit(0);
}

static void		display(t_constchar *lst_constchar, t_variable *lst_valeur
					, t_flags *lst_flags)
{
	while (lst_constchar || lst_valeur)
	{
		if (lst_constchar)
		{
			ft_putstr((char*)lst_constchar->content);
			lst_constchar = lst_constchar->next;
		}
		if (lst_valeur != NULL)
		{
			ft_putnbr((int)lst_valeur->content);
			lst_valeur = lst_valeur->next;
		}
	}
	printf("\n");
	while (lst_flags)
	{
		if (lst_flags)
		{
			printf("option		: %s\n", lst_flags->options);
			printf("Lenght_min	: %d\n", lst_flags->lenght_min);
			printf("preci		: %s\n", lst_flags->precis);
			printf("scale		: %d\n", lst_flags->scale);
			printf("type		: %c\n\n", lst_flags->type);
			lst_flags = lst_flags->next;
		}
	}
}

int			ft_printf(const char *format, ...)
{
	t_variable	*lst_valeur;
	t_constchar	*lst_constchar;
	t_flags		*lst_flags;
	va_list		args;

	va_start(args, format);
	lst_valeur = parsing(format, &lst_flags, &lst_constchar, args);
	display(lst_constchar, lst_valeur, lst_flags);
	va_end(args);
	return (0);
}
