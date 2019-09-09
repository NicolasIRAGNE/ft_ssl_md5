# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: niragne <niragne@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/18 12:01:42 by ldedier           #+#    #+#              #
#    Updated: 2019/09/09 17:22:26 by niragne          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

CC = gcc

UNAME = $(shell uname -m)

DEBUG ?= 0
OK_COLOR = \x1b[32;01m
EOC = \033[0m

CFLAGS = -DARCH=\"$(UNAME)\" -Wall -Wextra -Werror

ifeq ($(DEBUG), 1)
	LFLAGS += -fsanitize=address
	CFLAGS += -DDEBUG -fsanitize=address
endif

	CC += -g3

SRCDIR = srcs
SPEED = -j8
OBJDIR   = objs
OBJECTS	= $(addprefix $(OBJDIR)/, $(SRCS:%.c=%.o))

DEPS =		ft_ssl_md5.h

INCLUDES =	includes

LIBFTDIR =	./libft
LIBFT_INCLUDEDIR = $(LIBFTDIR)/includes
LIBFT = $(LIBFTDIR)/libft.a

SRCS =	main.c opts.c opts_2.c process_md5.c process_sha256.c swap.c debug.c md5_loops.c rotate.c\
		open_file.c ssl_perror.c tools.c sha256_tools.c

SRC	= $(addprefix $(SRCDIR)/, $(SRCS))
DEP = $(addprefix $(INCLUDES)/,$(DEPS))
INC = -I $(INCLUDES) -I $(LIBFT_INCLUDEDIR)

all:
	@make all -C $(LIBFTDIR)
	@make $(NAME)

libcompiled:
	@make $(NAME)

debug:
	@make all DEBUG=1

$(NAME): $(LIBFT) $(OBJECTS) $(DEP)
	$(CC) -o $(NAME) $(OBJECTS) $(LIBFT) $(LFLAGS) 

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) $(INC)

clean:
	@make clean -C $(LIBFTDIR)
	@rm -rf $(OBJECTS)

fclean: clean
	@make fclean -C $(LIBFTDIR)
	@rm -rf $(NAME)

re: fclean all
