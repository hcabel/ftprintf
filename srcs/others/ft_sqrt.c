/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 17:27:10 by hcabel            #+#    #+#             */
/*   Updated: 2019/04/10 19:04:18 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_sqrt(size_t nb)
{
	size_t i;

	i = 0;
	while (i * i != nb)
	{
		if (i * i > nb)
			return (0);
		i++;
	}
	return (i);
}