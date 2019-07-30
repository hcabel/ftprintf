/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 19:15:23 by hcabel            #+#    #+#             */
/*   Updated: 2019/07/30 17:03:29 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

typedef struct	s_flags
{
	char		options[5];
	int			length;
	int			precis;
	char		scale[2];
	char		type;
}				t_flags;

/*
**	ft_printf.c
*/
void			pf_error(char *reason); //useless
int				ft_printf(const char *format, ...);

/*
**	display.c
*/
int				pf_display(va_list args, char *str, int *ret);

/*
**	dispact.c
*/
int				pf_dispatch(t_flags flags, void *arg);

/*
**	utils.c
*/
int				add(char* add, char **str_addr, int start, int end);
int				fill(int size, char c, char **str_addr, int start);
int				ft_ubaselen(unsigned long long nbr, int base);
char			*ft_utoa_base(unsigned long long nbr, int base, char c);

/*
**	get_variable.c
*/
char			*convert_to_char(void *arg, t_flags flags, int *sign);


#endif
