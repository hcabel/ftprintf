/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 03:50:49 by sylewis           #+#    #+#             */
/*   Updated: 2019/08/02 13:10:06 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "printf.h"

static void    decimal_rounding(char **str_addr, int i)
{
    char    *str;

    str = *str_addr;
    while (str[i] == '9' && i >= 0)
    {
        str[i] = '0';
        i--;
        if (str[i] == '.')
            i--;
    }
        if (str[i] == '-')
        {
            str[1] = '1';
            str[0] = '-';
        }
        else if (i == 0)
            str[0] = '1';
        else if (str[i] != '9')
            str[i] += 1;
}

static void        decimal(char **str_addr, double deci, int precis, int len)
{
    int     i;
    char    *str;

    str = *str_addr;
    i = len;
    str[i++] = '.';
    while (precis > 1)
    {
        precis--;
        deci *= 10;
        str[i] = (long int)deci % 10 + '0';
        i++;
        deci -= (int)deci % 10;
    }
    i--;
    deci *= 10;
    if ((long int)deci % 10 >= 5)
    {
        if (str[i] != '9')
            str[i] += 1;
        else
        decimal_rounding(&str, i);
    }
}

static int	count(int n)
{
	int		i;
	int		nb;

	i = 0;
	nb = n;
	if (nb < 0)
		i++;
	while (nb != 0)
	{
		i++;
		nb = nb / 10;
	}
	return (i);
}

static void ft_itoa_float(char **str_addr, int n, int len)
{
    int sign;
    char    *str;

    str = *str_addr;
    sign = 1;
    if (n == 0)
        str[len] = '0';
    if (n < 0)
	{
		n = -n;
		sign = -1;
	}
	while (n > 0)
	{
		str[len--] = n % 10 + 48;
		n = n / 10;
	}
	if (sign == -1)
		str[len--] = '-';
}

static double      ft_dabs(double n)
{
    return (n > 0.0 ? n : -n);
}

char	    *ft_ftoa(double n, int precis)
{
    int     whole;
    int     len;
    char    *str;

    precis++;
    whole = (int)n;
    len = count(whole);
    if (!(str = (char*)ft_memalloc(sizeof(*str) * (len + precis + 2 + 1))))
        return (NULL);
    str[len + precis + 2] = '\0';
    ft_itoa_float(&str, whole, len);
    decimal(&str, ft_dabs(n - (double)whole), precis, len + 1);
    return(str[0] == '\0' ? str + 1 : str);
}





