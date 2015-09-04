/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karakhirn <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/09 14:21:52 by karakhirn         #+#    #+#             */
/*   Updated: 2015/09/04 12:38:40 by sdurr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void		usage(char *av)
{
	ft_putstr("Usage: ");
	ft_putstr(av);
	ft_putstr(" <port>\n");
	exit(-1);
}

static void		ft_pwd(int cs)
{
	char		buf1[1024];

	getcwd(buf1, 1023);
	send(cs, "SUCCESS\n", 9, MSG_OOB);
	send(cs, buf1, ft_strlen(buf1) + 1, MSG_OOB);
	send(cs, "\n", 2, MSG_OOB);
}

static int		ft_while(int cs, int sock, char *pwd)
{
	char		buf[1024];
	int			r;

	while (1)
	{
		r = read(cs, buf, 1023);
		buf[r - 1] = '\0';
		if (ft_strcmp(buf, "quit") == 0)
			ft_quit(sock, cs);
		else if (ft_strcmp(buf, "pwd") == 0)
			ft_pwd(cs);
		else if (ft_strcmp(buf, "ls") == 0)
			ft_ls(cs);
		else if (ft_strncmp(buf, "cd", 2) == 0)
			ft_cd(buf, pwd, cs);
		else if (ft_strncmp(buf, "get", 3) == 0)
			ft_get(buf, cs);
		else if (ft_strncmp(buf, "put", 3) == 0)
			ft_put(buf, cs);
		else if (buf[0])
			send(cs, "ERROR Command not found\n", 25, MSG_OOB);
		if (ft_strncmp(buf, "put", 3) != 0)
			send(cs, "", 2, 0);
		buf[0] = '\0';
	}
}

static void		ft_fork(int sock, char *pwd)
{
	int					cs;
	struct sockaddr_in	csin;
	unsigned int		cslen;

	cs = accept(sock, (struct sockaddr *)&csin, &cslen);
	if (fork() == 0)
		ft_while(cs, sock, pwd);
	else
		ft_fork(sock, pwd);
}

int				main(int ac, char **av)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;
	char				*pwd;
	char				buf[1023];

	pwd = ft_strdup(getcwd(buf, 1023));
	if (ac != 2)
		usage(av[0]);
	proto = getprotobyname("tcp");
	if (proto == 0)
		return (0);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(ft_atoi(av[1]));
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_putstr_fd("Bind error\n", 2);
		exit(2);
	}
	listen(sock, ft_atoi(av[1]));
	ft_fork(sock, pwd);
	close(sock);
	return (0);
}
