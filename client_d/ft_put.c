/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdurr <sdurr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/02 09:09:23 by sdurr             #+#    #+#             */
/*   Updated: 2015/09/03 12:01:50 by sdurr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	ft_put(char *buf, int sock)
{
	int		ret;
	char	buffer[1024];
	char	**tab;
	int		t;

	tab = ft_strsplit(buf, ' ');
	if ((ret = open(tab[1], O_RDONLY)) != -1)
	{
		while ((t = read(ret, buffer, 1023)) > 0)
		{
			buffer[t] = '\0';
			ft_putnbr(t);
			ft_putstr("\n");
			write(sock, buffer, t);
		}
	}
	close(ret);
	write(sock, "", 1);
}
