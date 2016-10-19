/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 20:27:50 by mcanal            #+#    #+#             */
/*   Updated: 2016/10/19 22:41:31 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

extern char **g_av;

char             *g_brute_char_list;
char             *g_print_buf;
char            **g_exec;
int               g_min = MIN_LENGTH;
int               g_max = MAX_LENGTH;
enum e_brute_flag g_flag = E_NOFLAG;

void        usage_error(void)
{
    printf("Usage: %s [OPTIONS] [COMMAND]\n", *g_av);
    printf(" --help: this help message\n");
    printf(" --echo,       -e: echo brute-words\n");
    printf(" --min LENGTH, -m LENGTH: minimum length of output (default: %d)\n", MIN_LENGTH);
    printf(" --max LENGTH, -M LENGTH: maximum length of output (default: %d)\n", MAX_LENGTH);
    printf("\nCharacters list(s) used for brute-forcing: (default: -P)\n");
    printf(" --lowercase,   -c: %s\n", LOWERCASE);
    printf(" --uppercase,   -C: %s\n", UPPERCASE);
    printf(" --letters,     -l: %s\n", LETTERS);
    printf(" --octdigits,   -o: %s\n", OCTDIGITS);
    printf(" --hexdigits,   -f: %s\n", HEXDIGITS);
    printf(" --lowerhexa,   -h: %s\n", LOWERHEXA);
    printf(" --upperhexa,   -H: %s\n", UPPERHEXA);
    printf(" --digits,      -d: %s\n", DIGITS);
    printf(" --punctuation, -p: %s\n", PUNCTUATION);
    printf(" --whitespaces, -w: %s\n", FAKE_WHITESPACES);
    printf(" --printable,   -P: %s\n", FAKE_PRINTABLE);
    exit(EXIT_FAILURE);
}

static void init_print_buf(void)
{
    g_print_buf = (char *)malloc(((size_t)g_max + 1) * sizeof(char));
    bzero(g_print_buf, (size_t)g_max + 1);
    memset(g_print_buf + g_max - g_min, *g_brute_char_list, (size_t)g_min);
}

static void init_brute_list(void)
{
    const char *brute_char_set[] = {
        DIGITS,
        LOWERCASE,
        UPPERCASE,
        LETTERS,
        PUNCTUATION,
        LOWERHEXA,
        UPPERHEXA,
        HEXDIGITS,
        OCTDIGITS,
        WHITESPACES,
        PRINTABLE,
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
        E_NOFLAG
    };

    int i;
    char *brute_swap;

    g_brute_char_list = (char *)malloc(512 * sizeof(char));
    bzero(g_brute_char_list, 512);
    /* if you really want to bruteforce more than 255 ascii chars, you deserve that segfault */

    i = 0;
    brute_swap = g_brute_char_list;
    while (brute_char_set[i])
    {
        if (g_flag & flag[i])
        {
            printf("g_flag:%d flag[%d]:%d\n", g_flag, i, flag[i]); /* DEBUG */
            strcpy(brute_swap, brute_char_set[i]);
            brute_swap += strlen(brute_swap); //... TODO
        }
        i++;
    }
    if (brute_swap == g_brute_char_list)
        strcpy(brute_swap, PRINTABLE);
}

static void init_exec(int len, char **av)
{
    char **exec_swap;

    g_exec = (char **)malloc(((size_t)len + 2) * sizeof(char *));
    bzero(g_exec, ((size_t)len + 2) * sizeof(char *));
    exec_swap = g_exec;
    while (*av)
        *exec_swap++ = *av++;
    *exec_swap = (char *)-42;
}

static void init(int len, char **av)
{
    if (len)
        init_exec(len, av);
    else
        g_flag |= E_ECHO;

    init_brute_list();
    init_print_buf();
    //TODO: print a pretty message before going on? (allow to abort there -.-)
}

void        parse(int ac, char **av)
{
    if (!*av)
    {
        init(FALSE, av);
        return;
    }
    if (**av != '-')
    {
        init(ac - (int)(av - g_av), av);
        return;
    }

    if (!strcmp(*av, "--help"))
        usage_error();
    else if (!strcmp(*av, "-m") || !strcmp(*av, "--min"))
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
    else
        parse_flags(av);

    parse(ac, av + 1);
}
