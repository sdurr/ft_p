
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karakhirn <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/09 14:21:52 by karakhirn         #+#    #+#             */
/*   Updated: 2015/08/24 14:47:16 by karakhirn        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "libft/get_next_line.h"

void		usage(char *av)
{
	ft_putstr("Usage: ");
	ft_putstr(av);
	ft_putstr(" <addr> <port>\n");
	exit(-1);
}

int			ft_create_client(char *addr, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return (0);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_putstr( "Connect error\n");
		exit (2);
	}	
	return (sock);

}

int			test(int sock) 
{
	int		r;
	char	buf[1024];
	
	while ((r = recv(sock, buf, sizeof(buf), 0)) > 0)
	{
		buf[r] = 0;
		if ((ft_strcmp(buf, "") == 0))
			return 0;
		write(1, buf, r);
	}
	return 0;
}

void		ft_put(char *buf, int sock)
{
	int		ret;
	char	buffer[1023];
	char	 **tab;
	int		t;
	
	tab = ft_strsplit(buf, ' ');
	ret = open(tab[1], O_RDONLY);
	while ((t = read(ret, buffer, 1023)) > 0)
	{
		buffer[t] = 0;
		write(sock, buffer, t);
	}
	write(sock, "", 0);
	close(ret);	
}

void		ft_get(char *buf, int sock)
{
	int		ret;
	int		r;
	char	 **tab;
	
	tab = ft_strsplit(buf, ' ');
	if ((ret = open(tab[1], O_RDWR | O_CREAT | O_EXCL, 00777 )) == -1)
		ft_putstr("This files already exit\n");
	while ((r = recv(sock, buf, sizeof(buf), 0)) > 0)
	{
		buf[r] = 0;
		if ((ft_strcmp(buf, "") == 0))
			break ;
		write(ret, buf, r);
	}
	close(ret);
}

int			 main( int ac, char **av)
{
	int port;
	int sock;
	char buf[1023];
	int r;

	if (ac != 3)
		usage (av[0]);
	port = ft_atoi(av[2]);
	sock = ft_create_client(av[1], port);
	while (1)
	{
		write(1, "$> ", 3);
		r = read(0, buf, 1023);
		buf[r -1] = 0;
		write(sock, buf, r);
		if (ft_strcmp(buf, "quit") == 0)
			break ;
		if (ft_strncmp(buf, "put", 3) == 0)
			ft_put(buf, sock);
		else if (ft_strncmp(buf, "get", 3) == 0)
			ft_get(buf, sock);
		else
			test(sock);
	}
	close(sock);
	return (0);
}