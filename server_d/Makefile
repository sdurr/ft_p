#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdurr <sdurr@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/06/04 10:34:39 by sdurr             #+#    #+#              #
#    Updated: 2015/09/02 11:05:27 by sdurr            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		= server

SRC			= server.c \
				ft_put.c \
				ft_get.c \
				ft_cd.c \
				ft_ls.c \
				quit.c \

OBJ			= $(SRC:.c=.o)

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror


PATHLIB    = -I libft/includes

$(NAME)	:		$(OBJ)
				@make -C libft
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L libft -lft

clean	:
				rm -rf $(OBJ)

all		:		$(NAME)

fclean	:		clean
				rm -rf $(NAME)

re		:		fclean all

.c.o	:
				@$(CC) $(CFLAGS) $(PATHLIB) -o $@ -c $<
