/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 19:55:44 by mcanal            #+#    #+#             */
/*   Updated: 2016/10/19 21:45:02 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

/*
** define
*/
# define PARSER_H

# define DIGITS       "0123456789"
# define LOWERCASE    "abcdefghijklmnopqrstuvwxyz"
# define UPPERCASE    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define LETTERS      LOWERCASE UPPERCASE
# define PUNCTUATION  "!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~"
/* # define PUNCTUATION  "!#$%&()*+,-./:;<=>?@[\\]^_{|}~" */ //without quotes
# define LOWERHEXA    DIGITS "abcdef"
# define UPPERHEXA    DIGITS "ABCDEF"
# define HEXDIGITS    DIGITS "abcdef" "ABCDEF"
# define OCTDIGITS    "01234567"
# define WHITESPACES  " \t\n\r\x0b\x0c"
# define PRINTABLE    DIGITS LETTERS PUNCTUATION WHITESPACES

# define FAKE_WHITESPACES  " \\t\\n\\v\\f\\r"
# define FAKE_PRINTABLE    DIGITS LETTERS PUNCTUATION FAKE_WHITESPACES

# define MIN_LENGTH 1
# define MAX_LENGTH 42

/*
** include
*/
# include <brute.h>

/*
** parse_flags.c
*/
void parse_flags(char **av);

#endif
