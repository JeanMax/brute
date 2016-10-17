/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 20:27:50 by mcanal            #+#    #+#             */
/*   Updated: 2016/10/17 21:24:05 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

extern char **g_av;

char  *g_print_buf;
char  *g_brute_char_list;
char **g_exec;
int    g_min = MIN_LENGTH;
int    g_max = MAX_LENGTH;

static void init()
{
    g_print_buf = (char *)malloc((g_max + 1) * sizeof(char));
    g_brute_char_list = (char *)malloc(256 * sizeof(char));
    bzero(g_print_buf, g_max + 1);
    bzero(g_brute_char_list, 256);
    strcpy(g_brute_char_list, DIGITS LETTERS PUNCTUATION);
    memset(g_print_buf + g_max - g_min, *g_brute_char_list, g_min);
}

static void init_exec(int len, char **av)
{
    char **exec_swap;

    g_exec = (char **)malloc((len + 2) * sizeof(char *));
    bzero(g_exec, (len + 2) * sizeof(char *));
    exec_swap = g_exec;
    while (*av)
        *exec_swap++ = *av++;
    *exec_swap = (char *)-42;
}

void parse(int ac, char **av)
{
    if (!*av)
        return init();

    if (**av != '-')
    {
        init_exec(ac - (int)(av - g_av), av);
        return init();
    }

    if (!strcmp(*av, "-m") || !strcmp(*av, "--min"))
    {
        g_min = atoi(*++av);
        if (g_min > g_max || g_min < 1)
            usage_error();
    }
    else if (!strcmp(*av, "-M") || !strcmp(*av, "--max"))
    {
        g_max = atoi(*++av);
        if (g_max < g_min)
            usage_error();
    }


    parse(ac, av + 1);
}
