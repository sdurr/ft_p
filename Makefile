#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdurr <sdurr@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/06/04 10:34:39 by sdurr             #+#    #+#              #
#    Updated: 2015/08/24 14:19:07 by karakhirn        ###   ########.fr        #
#                                                                              #
#******************************************************************************#

all		:	
			make -C server_d	
			make -C client_d
			cp server_d/server .
			cp client_d/client .

clean   :
			make fclean -C client_d
			make fclean -C server_d		

fclean	: clean
		rm client
		rm server
