/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdurr <sdurr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/02 09:09:23 by sdurr             #+#    #+#             */
/*   Updated: 2015/09/02 09:12:25 by sdurr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	ft_put(char *buf, int sock)
{
	int		ret;
	char	buffer[1023];
	char	**tab;
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
