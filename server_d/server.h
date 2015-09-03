/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdurr <sdurr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/02 09:58:35 by sdurr             #+#    #+#             */
/*   Updated: 2015/09/03 11:37:41 by sdurr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		SERVER_H
# define	SERVER_H

#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <fcntl.h>

int			ft_put(char *buf, int cs);
void		ft_get(char *buf, int cs);
void		ft_cd(char *buf, char *pwd, int cs);
void		ft_ls(int cs);
void		ft_quit(int sock, int cs);

#endif
