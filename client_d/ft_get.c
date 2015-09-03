/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdurr <sdurr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/02 09:11:38 by sdurr             #+#    #+#             */
/*   Updated: 2015/09/03 10:26:17 by sdurr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	ft_get(char *buf, int sock)
{
	int		ret;
	int		r;
	char	**tab;

	tab = ft_strsplit(buf, ' ');
	if ((ret = open(tab[1], O_RDWR | O_CREAT | O_EXCL, 00777)) == -1)
		ft_putstr("This files already exit\n");
	while ((r = recv(sock, buf, sizeof(buf), 0)) > 0)
	{
		buf[r] = 0;
		if ((ft_strcmp(buf, "") == 0))
			break ;
		write(ret, buf, r);
	}
	close(ret);
	if (ret != -1)
		ft_putstr("SUCCESS\n");
}
