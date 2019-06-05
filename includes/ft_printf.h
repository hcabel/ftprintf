/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 14:00:54 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/04 17:08:33 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <stdarg.h>

typedef struct			s_variable
{
	void				*content;
	struct s_variable	*next;
}						t_variable;

typedef struct			s_constchar
{
	char				*content;
	struct s_constchar	*next;
}						t_constchar;

typedef struct			s_flags
{
	char				*options;
	int					lenght_min;
	char				*precis;
	int					scale;
	char				type;
	struct s_flags		*next;
}						t_flags;

/*
**	ft_printf.c
*/
void					finish(char *reason);
int						ft_printf(const char *format, ...);

/*
**	parsing.c
*/
t_variable				*parsing(const char *format, t_flags **lst_flags,
							t_constchar **lst_constchar, va_list args);

/*
**	stock_variable.c
*/
t_variable				*stock_variable(int args_nb, va_list args);

/*
**	stock_flags.c
*/
int					new_arg(t_flags **lst_flags, const char *str, int i);

#endif
