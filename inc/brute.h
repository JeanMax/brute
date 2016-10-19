/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brute.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 19:55:44 by mcanal            #+#    #+#             */
/*   Updated: 2016/10/19 22:04:01 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRUTE_H

/*
** define
*/
# define BRUTE_H

# define TRUE  1
# define FALSE 0

/*
** include
*/
# include <stdlib.h> //BASE only
# include <stdio.h>
# include <string.h>


/*
** enum
*/
enum                    e_brute_flag
{
    E_NOFLAG = 0,
    E_DIGITS = (1 << 0),
    E_LOWERCASE = (1 << 1),
    E_UPPERCASE = (1 << 2),
    E_LETTERS = (1 << 3),
    E_PUNCTUATION = (1 << 4),
    E_LOWERHEXA = (1 << 5),
    E_UPPERHEXA = (1 << 6),
    E_HEXDIGITS = (1 << 7),
    E_OCTDIGITS = (1 << 8),
    E_WHITESPACES = (1 << 9),
    E_PRINTABLE = (1 << 10),
    E_ECHO = (1 << 11)
};

/*
** PARSER
** parse.c
*/
void usage_error();
void parse(int ac, char **av);

/*
** DOER
** do.c
*/
void brute_loop();

#endif
