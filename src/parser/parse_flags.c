/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 21:39:27 by mcanal            #+#    #+#             */
/*   Updated: 2016/10/19 22:31:35 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

extern enum e_brute_flag g_flag;

void        parse_flags(char **av)
{
    //TODO: use this 3 arrays in usage_error()
    const char *long_flag[] = {
        "--digits",
        "--lowercase",
        "--uppercase",
        "--letters",
        "--punctuation",
        "--lowerhexa",
        "--upperhexa",
        "--octdigits",
        "--hexdigits",
        "--whitespaces",
        "--printable",
        "--echo",
        NULL
    };

    const char *short_flag[] = {
        "-d",
        "-c",
        "-C",
        "-l",
        "-p",
        "-h",
        "-H",
        "-o",
        "-f",
        "-w",
        "-P",
        "-e",
        NULL
    };

    const enum e_brute_flag flag[] = {
        E_DIGITS,
        E_LOWERCASE,
        E_UPPERCASE,
        E_LETTERS,
        E_PUNCTUATION,
        E_LOWERHEXA,
        E_UPPERHEXA,
        E_HEXDIGITS,
        E_OCTDIGITS,
        E_WHITESPACES,
        E_PRINTABLE,
        E_ECHO,
        E_NOFLAG
    };

    int i;

    i = 0;
    while (short_flag[i] \
           && strcmp(short_flag[i], *av) \
           && strcmp(long_flag[i], *av))
        i++;

    if (!short_flag[i])
        usage_error();

    g_flag |= flag[i];
}
