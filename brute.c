#define DIGITS       "0123456789"
#define LOWERCASE    "abcdefghijklmnopqrstuvwxyz"
#define UPPERCASE    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LETTERS      LOWERCASE UPPERCASE
#define PUNCTUATION  "!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~"
/* #define PUNCTUATION  "!#$%&()*+,-./:;<=>?@[\\]^_{|}~" */ //without quotes
#define LOWERHEXA    DIGITS "abcdef"
#define UPPERHEXA    DIGITS "ABCDEF"
#define HEXDIGITS    DIGITS "abcdef" "ABCDEF"
#define OCTDIGITS    "01234567"
#define WHITESPACES  " \t\n\r\x0b\x0c"
#define FAKE_WHITESPACES  " \\t\\n\\v\\f\\r"
#define PRINTABLE    DIGITS LETTERS PUNCTUATION WHITESPACES
#define FAKE_PRINTABLE    DIGITS LETTERS PUNCTUATION FAKE_WHITESPACES

#define TRUE  1
#define FALSE 0

#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#define MIN_LENGTH 1
#define MAX_LENGTH 42

extern char **environ;

char   *g_print_buf;
char   g_brute_char_list[256];
char **g_av;
char **g_exec;
int    g_min = MIN_LENGTH;
int    g_max = MAX_LENGTH;

static void usage_error()
{
    printf("Usage: %s [OPTIONS] COMMAND\n", *g_av);
    printf(" --help: this help message\n");
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

static void print_word()
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

static void brute_loop()
{
    char *print_swap;
    char *brute_swap;

    print_swap = g_print_buf + g_max - 1;
    do {
        brute_swap = g_brute_char_list;
        while (*brute_swap)
        {
            *print_swap = *(brute_swap++);
            print_word();
        }
    } while (carry_on(*(brute_swap - 1), g_print_buf + g_max - 1));
}

static void init()
{
    g_print_buf = (char *)malloc((g_max + 1) * sizeof(char));
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

static void parse(int ac, char **av)
{
    if (!*av)
        return;

    if (**av != '-')
    {
        init_exec(ac - (int)(av - g_av), av);
        return;
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

int		    main(int ac, char **av)
{
    g_av = av;
    if (ac < 2)
        usage_error();

    parse(ac, av + 1);
    init();
    brute_loop();

	return (EXIT_SUCCESS);
}
