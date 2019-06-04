/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 14:00:54 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/03 15:43:10 by hcabel           ###   ########.fr       */
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
	char				*content;
	struct s_variable	*next;
}						t_variable;

/*
**	ft_printf.c
*/
int						ft_printf(const char *format, ...);

/*
**	set_variable.c
*/
t_variable				*stock_variable(int nb_args, ...);

#endif
