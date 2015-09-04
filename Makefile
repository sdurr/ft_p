#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdurr <sdurr@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/06/04 10:34:39 by sdurr             #+#    #+#              #
#    Updated: 2015/09/04 12:08:43 by sdurr            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

all		:	client server

client	:
			make -C client_d

server	:
			make -C server_d

clean   :
			make clean -C client_d
			make clean -C client_d/libft
			make clean -C server_d
			make clean -C server_d/libft

fclean	: clean
			make fclean -C client_d
			make fclean -C client_d/libft
			make fclean -C server_d
			make fclean -C server_d/libft

re		: fclean all