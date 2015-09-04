/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karakhirn <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/09 14:21:52 by karakhirn         #+#    #+#             */
/*   Updated: 2015/09/04 12:43:26 by sdurr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void			usage(char *av)
{
	ft_putstr("Usage: ");
	ft_putstr(av);
	ft_putstr(" <addr> <port>\n");
	exit(-1);
}

static int			ft_create_client(char *addr, int port)
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
		ft_putstr("Connect error\n");
		exit(2);
	}
	return (sock);
}

static int			test(int sock)
{
	int		r;
	char	buf[1024];

	while ((r = recv(sock, buf, sizeof(buf), 0)) > 0)
	{
		buf[r] = 0;
		if ((ft_strcmp(buf, "") == 0))
			return (0);
		if ((ft_strncmp(buf, "ERROR", 5) == 0))
		{
			write(1, buf, r);
			return (-1);
		}
		write(1, buf, r);
	}
	return (0);
}

int					main(int ac, char **av)
{
	int		sock;
	char	buf[1023];
	int		r;

	if (ac != 3)
		usage(av[0]);
	sock = ft_create_client(av[1], ft_atoi(av[2]));
	while (1)
	{
		write(1, "$> ", 3);
		r = read(0, buf, 1023);
		buf[r - 1] = 0;
		write(sock, buf, r);
		if (ft_strcmp(buf, "quit") == 0)
			break ;
		if (ft_strncmp(buf, "put", 3) == 0)
		{
			r = test(sock);
			if (r > -1)
			{
				ft_put(buf, sock);
				ft_putstr("SUCCESS\n");
			}
		}
		else if (ft_strncmp(buf, "get", 3) == 0)
			ft_get(buf, sock);
		else
			test(sock);
	}
	close(sock);
	return (0);
}
