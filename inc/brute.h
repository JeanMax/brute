/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brute.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 19:55:44 by mcanal            #+#    #+#             */
/*   Updated: 2016/10/17 20:39:29 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRUTE_H

/*
** define
*/
# define BRUTE_H

#  define DIGITS       "0123456789"
#  define LOWERCASE    "abcdefghijklmnopqrstuvwxyz"
#  define UPPERCASE    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#  define LETTERS      LOWERCASE UPPERCASE
#  define PUNCTUATION  "!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~"
/* #  define PUNCTUATION  "!#$%&()*+,-./:;<=>?@[\\]^_{|}~" */ //without quotes
#  define LOWERHEXA    DIGITS "abcdef"
#  define UPPERHEXA    DIGITS "ABCDEF"
#  define HEXDIGITS    DIGITS "abcdef" "ABCDEF"
#  define OCTDIGITS    "01234567"
#  define WHITESPACES  " \t\n\r\x0b\x0c"
#  define PRINTABLE    DIGITS LETTERS PUNCTUATION WHITESPACES

#  define FAKE_WHITESPACES  " \\t\\n\\v\\f\\r"
#  define FAKE_PRINTABLE    DIGITS LETTERS PUNCTUATION FAKE_WHITESPACES

#  define TRUE  1
#  define FALSE 0

#define MIN_LENGTH 1
#define MAX_LENGTH 42

/*
** include
*/
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


/*
** enum
*/
enum					e_error
{
	E_NOERROR = 0,
	E_NOEXIT = (1 << 0),
	E_CMDNOTFOUND = (1 << 1),
	E_NOSUCHFILE = (1 << 2),
	E_OPEN = (1 << 3),
	E_PIPE = (1 << 4),
	E_FORK = (1 << 5),
	E_ARG = (1 << 6),
	E_PATH = (1 << 7),
	E_TTY = (1 << 8),
	E_GETATTR = (1 << 9),
	E_SETATTR = (1 << 10),
	E_TERM = (1 << 11)
};

/*
** BASE
** main.c
*/
void usage_error();

/*
** PARSER
** parse.c
*/
void parse(int ac, char **av);

/*
** DOER
** do.c
*/
void brute_loop();

#endif
