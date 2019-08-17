/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sylewis <sylewis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 20:02:13 by sylewis           #+#    #+#             */
/*   Updated: 2019/08/16 23:03:36 by sylewis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

void    colours(char *tab[6])
{
    tab[0] = MAGENTA;
    tab[1] = RED;
    tab[2] = YELLOW;
    tab[3] = GREEN;
    tab[4] = CYAN;
    tab[5] = BLUE;
}

void    rainbow(char *str, char *tab[6])
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i] != '\0')
    {
        write(1, tab[j], 6);
        j++;
        if (j > 5)
            j = 0;
        write(1, str + i, 1);
        i++;
    }
    write(1, &"\n", 1);
}

/*
void    move_chars(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    while (i != 0)
    {
        str[i * 2] = str[i];
        str[i * 2 - 1] = ' ';
        i--;
    }
}

void    vaporwave(char **str_addr)
{
    char *str;

    str = *str_addr;
    while (str[i] != '\0')
    {
        move_chars(str, 1);
    }
}
*/

int     colour_parse(char *str)
{
    int i;

    i = 0;
    if (str[i] == '{' && str[i + 2] == '}')
    {
        if (str[i + 1] == 'r')
            write(1, &RED, 6);
        else if (str[i + 1] == 'g')
            write(1, &GREEN, 6);
        else if (str[i + 1] == 'y')
            write(1, &YELLOW, 6);
        else if (str[i + 1] == 'b')
            write(1, &BLUE, 6);
        else if (str[i + 1] == 'm')
            write(1, &MAGENTA, 6);
        else if (str[i + 1] == 'c')
            write(1, &CYAN, 6);
        else if (str[i + 1] == '/')
            write(1, &RESET, 6);
        else
            return (0);
        return (3);
    }
    return (0);
}

