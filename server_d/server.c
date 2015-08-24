/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karakhirn <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/09 14:21:52 by karakhirn         #+#    #+#             */
/*   Updated: 2015/08/24 15:30:57 by karakhirn        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft/get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>

void		usage(char *av)
{
	ft_putstr("Usage: ");
	ft_putstr(av);
	ft_putstr(" <port>\n");
	exit(-1);
}

void		ft_ls(int cs)
{
	DIR				*dirp;
	struct dirent	*read;
	char			*file;
	
	if ((dirp = opendir(".")) != NULL)
	{
		send(cs, "SUCCESS\n", 9, MSG_OOB);
		while ((read = readdir(dirp)) != NULL)
		{
			file = ft_strdup(read->d_name);
			send(cs, file, ft_strlen(file) + 1, MSG_OOB);
			send(cs, "\n", 2, MSG_OOB);
		}
	}
}

void		ft_cd(char *buf, char *pwd, int cs)
{
	char **tab;
	int success;

	success = 0;
	tab = ft_strsplit(buf, ' ');
	if (tab[1])
	{
		if (chdir(tab[1]) == -1)
			send(cs, "ERROR this directory does not exist \n", 38, MSG_OOB);
		else
			success = 1;
	}
	else
		chdir("~");
	if (ft_strncmp(pwd, getcwd(buf, 1023), ft_strlen(pwd)) != 0)
	{
		send(cs, "ERROR you don't have a permission\n", 35, MSG_OOB);
		chdir(pwd);
	}
	else if (success == 1)
		send(cs, "SUCCESS\n", 9, MSG_OOB);
}

void		ft_get(char *buf, int cs)
{
	int		ret;
	char	 buf3[1024];
	char	 **tab;
	int		r;
	tab = ft_strsplit(buf, ' ');
	if ((ret = open(tab[1], O_RDONLY)) < 0)
		send(cs, "ERROR File not exist\n", 27, MSG_OOB);
	else
	{
		while ((r = read(ret, buf3, 1023)) > 0)
		{
			buf3[r] = 0;
			send(cs, buf3, r + 1, MSG_OOB);
		}
		close(ret);
		send(cs, "SUCCESS\n", 9, MSG_OOB);
	}
}

void		ft_put(char *buf, int cs)
{
	int ret;
	char buf4[1024];
	int r;
	char **tab;

	tab = ft_strsplit(buf, ' ');
	if ((ret = open(tab[1], O_RDWR | O_CREAT | O_EXCL, 00777 )) == -1)
		send(cs, "ERROR this file already exist\n", 31, MSG_OOB);
	while ((r = read(cs, buf4, 1023)) > 0)
	{
		buf4[r] = 0;
		if (ft_strcmp(buf4, "") == 0)
			break ;
		write(ret, buf4, r);
		if (r < 1023)
			break;
	}
	send(cs, "SUCCESS\n", 9, MSG_OOB);
	close(ret);
}

void		ft_pwd(int cs)
{
	char		 buf1[1024];

	getcwd(buf1, 1023);
	send(cs, "SUCCESS\n", 9, MSG_OOB);
	send(cs, buf1, ft_strlen(buf1) + 1, MSG_OOB);
	send(cs, "\n", 2, MSG_OOB);
}

int			ft_while(int cs, int sock, char *pwd)
{
	char		buf[1024];
	int			r;

	while(1)
	{
		r = read(cs, buf, 1023);
		buf[r - 1] = '\0';
		if (ft_strcmp(buf, "quit") == 0)
		{
			close(cs);
			close(sock);
			exit(0);
		}
		else if(ft_strcmp(buf, "pwd") == 0)
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
		send(cs, "", 2, 0);
	}
}

void		ft_fork(int sock, char *pwd)
{
	int					cs;
	struct sockaddr_in	csin;
	unsigned int		cslen;

	cs = accept(sock, (struct sockaddr *)&csin, &cslen);
	if (fork() == 0)
		ft_while(cs, sock, pwd);
	else
		ft_fork( sock, pwd);
} 

int			main(int ac, char **av)
{
	int					port;
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;
	char				*pwd;
	char				buf[1023];

	pwd = ft_strdup(getcwd(buf, 1023));
	if (ac != 2)
		usage (av[0]);
	port = ft_atoi(av[1]);
	proto = getprotobyname("tcp");
	if (proto == 0)
		return (0);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_putstr("Bind error");
		exit (2);
	}
	listen(sock, port);
	ft_fork(sock, pwd);
	close(sock);
	return (0);
}
