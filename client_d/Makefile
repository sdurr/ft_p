#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdurr <sdurr@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/06/04 10:34:39 by sdurr             #+#    #+#              #
#    Updated: 2015/09/04 12:06:02 by sdurr            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		= client
SRC			= client.c \
				ft_put.c \
				ft_get.c \

OBJ			= $(SRC:.c=.o)

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror


PATHLIB    = -I libft/includes

$(NAME)	:		libft $(OBJ)
				@make -C libft
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L libft -lft

clean	:
				@rm -rf $(OBJ)

all		:		$(NAME)

fclean	:		clean
				@rm -rf $(NAME)

re		:		fclean all

.c.o	:
				@$(CC) $(CFLAGS) $(PATHLIB) -o $@ -c $<
