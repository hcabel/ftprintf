/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 13:35:56 by hcabel            #+#    #+#             */
/*   Updated: 2019/06/06 14:23:13 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_cast_char(void *arg)
{
	ft_putchar((char)arg);
}

void	put_cast_str(void *arg)
{
	ft_putstr((char*)arg);
}
