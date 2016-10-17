/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 20:13:53 by mcanal            #+#    #+#             */
/*   Updated: 2016/10/17 21:18:45 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brute.h"

char **g_av;

void usage_error()
{
    printf("Usage: %s [OPTIONS] [COMMAND]\n", *g_av);
    /* printf(" --help: this help message\n"); */
	/* printf(" --echo,       -e: echo brute-words\n"); */
    printf(" --min LENGTH, -m LENGTH: minimum length of output (default: %d)\n", MIN_LENGTH);
    printf(" --max LENGTH, -M LENGTH: maximum length of output (default: %d)\n", MAX_LENGTH);
    /* printf("\nCharacters list(s) used for brute-forcing: (default: -P)\n"); */
    /* printf(" --lowercase,   -c: %s\n", LOWERCASE); */
    /* printf(" --uppercase,   -C: %s\n", UPPERCASE); */
    /* printf(" --letters,     -l: %s\n", LETTERS); */
    /* printf(" --octdigits,   -o: %s\n", OCTDIGITS); */
    /* printf(" --hexdigits,   -f: %s\n", HEXDIGITS); */
    /* printf(" --lowerhexa,   -h: %s\n", LOWERHEXA); */
    /* printf(" --upperhexa,   -H: %s\n", UPPERHEXA); */
    /* printf(" --digits,      -d: %s\n", DIGITS); */
    /* printf(" --punctuation, -p: %s\n", PUNCTUATION); */
    /* printf(" --whitespaces, -w: %s\n", FAKE_WHITESPACES); */
    /* printf(" --printable,   -P: %s\n", FAKE_PRINTABLE); */
    exit(EXIT_FAILURE);
}

int main(int ac, char **av)
{
    g_av = av;
    if (ac < 2)
        usage_error();

    parse(ac, av + 1);
    brute_loop();

	return (EXIT_SUCCESS);
}
