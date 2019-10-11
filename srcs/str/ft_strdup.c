/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:18:35 by hcabel            #+#    #+#             */
/*   Updated: 2019/04/10 19:04:09 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*tab;
	int		size;

	i = 0;
	if (!(tab = (char*)malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (0);
	size = ft_strlen(s1) + 1;
	while (i < size)
	{
		tab[i] = s1[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
