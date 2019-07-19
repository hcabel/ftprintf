/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 23:44:26 by hcabel            #+#    #+#             */
/*   Updated: 2019/07/15 23:44:42 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fill(int size, char c)
{
	char	*str;
	int		i;

	if (size < 0 || (str = (char*)malloc(sizeof(char) * size)) == NULL)
		return ;
	i = 0;
	while (i < size)
		str[i++] = c;
	write(1, str, size);
	free(str);
}
