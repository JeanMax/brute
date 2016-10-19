#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/29 13:16:03 by mcanal            #+#    #+#              #
#    Updated: 2016/10/17 22:06:38 by mcanal           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =	brute

C_SRC =	main.c
C_DOER = do.c
C_PARSER = parse.c parse_flags.c

O_DIR = obj
C_DIR = src
I_DIR =	-I./inc/
VPATH =	src:src/parser:src/doer

SRCC = 	$(C_SRC:%.c=src/%.c)		$(C_PARSER:%.c=src/builtin/%.c)	\
		$(C_DOER:%.c=src/redirection/%.c)
OBJS =	$(C_SRC:%.c=$(O_DIR)/%.o)	$(C_PARSER:%.c=$(O_DIR)/%.o) \
		$(C_DOER:%.c=$(O_DIR)/%.o)
DEPS =  $(OBJS:%.o=%.d)

LIB =

MAKE =		make -j
RM =		rm -rf
MKDIR =		mkdir -p
CC =		$(shell clang --version >/dev/null 2>&1 && echo clang || echo gcc)

CFLAGS =	-Wall -Wextra -Werror -O2

ifeq ($(OS), Windows_NT)
  CCFLAGS += -D WIN32
  ifeq ($(PROCESSOR_ARCHITECTURE), AMD64)
    CCFLAGS += -D AMD64
  else ifeq ($(PROCESSOR_ARCHITECTURE), x86)
    CCFLAGS += -D IA32
  endif
else
  UNAME_S = $(shell uname -s)
  ifeq ($(UNAME_S), Linux)
    CCFLAGS += -D LINUX
  else ifeq ($(UNAME_S), Darwin)
    CCFLAGS += -D OSX
  endif
  UNAME_P = $(shell uname -p)
  ifeq ($(UNAME_P), x86_64)
    CCFLAGS += -D AMD64
  else ifneq ($(filter %86, $(UNAME_P)), )
    CCFLAGS += -D IA32
  else ifneq ($(filter arm%, $(UNAME_P)), )
    CCFLAGS += -D ARM
  endif
endif

WHITE =	\033[37;01m
RED =	\033[31;01m
GREEN =	\033[32;01m
BLUE =	\033[34;01m
BASIC =	\033[0m

.PHONY: all debug sanitize me_cry clean fclean re

all:
	@$(MAKE) $(NAME)

debug:
	@$(MAKE) $(NAME) "CFLAGS = -g -ggdb"

sanitize:
	@$(MAKE) $(NAME) \
		"CFLAGS = -g -ggdb -fsanitize=address,undefined -ferror-limit=5"

me_cry:
	@$(MAKE) $(NAME) \
		"CFLAGS = -Wpedantic -Wshadow -Wconversion -Wcast-align \
-Wstrict-prototypes -Wmissing-prototypes -Wunreachable-code -Winit-self \
-Wmissing-declarations -Wfloat-equal -Wbad-function-cast -Wundef \
-Waggregate-return -Wstrict-overflow=5 -Wold-style-definition -Wpadded \
-Wredundant-decls -Wall -Werror -Wextra" #-Wcast-qual

-include $(DEPS)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(I_DIR) $(OBJS) -o $@ $(LIB)
	@echo "$(BLUE)$(OBJS) $(WHITE)->$(RED) $@ $(BASIC)"
	@echo "$(WHITE)flags:$(BASIC) $(CFLAGS)"
	@echo "$(WHITE)compi:$(BASIC) $(CC)"

$(O_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) $(I_DIR) -MMD -c $< -o $@
	@echo "$(WHITE)$<\t->$(BLUE) $@ $(BASIC)"

$(OBJS): | $(O_DIR)

$(O_DIR):
	@$(MKDIR) $(O_DIR)
	@echo "$(O_DIR)" > .gitignore
	@echo "$(NAME)" >> .gitignore

clean:
	@$(RM) $(O_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
