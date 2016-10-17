/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 20:37:58 by mcanal            #+#    #+#             */
/*   Updated: 2016/10/17 21:19:38 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doer.h"

extern char **environ;

extern char **g_av;

extern char  *g_print_buf;
extern char  *g_brute_char_list;
extern char **g_exec;
extern int    g_min;
extern int    g_max;

static void exec_with_arg()
{
    char *print_swap;
    char **exec_swap;
    pid_t zboub;

    print_swap = g_print_buf;
    while (!*print_swap && print_swap - g_print_buf < g_max)
        print_swap++;
    printf("<%s>\n", print_swap); /* DEBUG */

    exec_swap = g_exec;
    while (*exec_swap)
        exec_swap++;
    *(exec_swap - 1) = print_swap;

    if ((zboub = fork()) < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
	else if (!zboub)
	{
        execve(*g_exec, g_exec, environ);
        perror("execve");
        exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
}

static int  carry_on(char carry_char, char *print_swap)
{
    if (!*print_swap)
    {
        *print_swap = *g_brute_char_list;
        return (TRUE);
    }
    if (print_swap == g_print_buf && *print_swap == carry_char)
        return (FALSE);
    if (!(*print_swap = *(strchr(g_brute_char_list, *print_swap) + 1)))
    {
        *print_swap = *g_brute_char_list;
        return (carry_on(carry_char, print_swap - 1));
    }
    return (TRUE);
}

void brute_loop()
{
    char *print_swap;
    char *brute_swap;

    print_swap = g_print_buf + g_max - 1;
    do {
        brute_swap = g_brute_char_list;
        while (*brute_swap)
        {
            *print_swap = *(brute_swap++);
            exec_with_arg();
        }
    } while (carry_on(*(brute_swap - 1), g_print_buf + g_max - 1));
}
