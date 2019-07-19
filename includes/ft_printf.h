/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 19:15:23 by hcabel            #+#    #+#             */
/*   Updated: 2019/07/15 23:45:44 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>

# include <stdio.h>

typedef struct			s_flags
{
	char			    options[5];
	int					length;
	int					precis;
	char				scale[2];
	char				type;
}						t_flags;

/*
**	ft_printf.c
*/
void					pf_error(char *reason); //useless
int						ft_printf(const char *format, ...);

/*
**	display.c
*/
int						pf_display(va_list args, char *str);

/*
**	dispact.c
*/
void					pf_dispatch(t_flags flags, void *arg);

/*
**	utils.c
*/
void					fill(int size, char c);

#endif
