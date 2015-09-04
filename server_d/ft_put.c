/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdurr <sdurr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/02 10:03:06 by sdurr             #+#    #+#             */
/*   Updated: 2015/09/04 16:02:30 by sdurr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		test(int cs, char **tab)
{
	int	ret;

	if ((ret = open(tab[1], O_RDONLY)) != -1)
	{
		send(cs, "error\n", 7, MSG_OOB);
		close(ret);
		return (-1);
	}
	send(cs, "", 2, 0);
	return (0);
}

int		ft_put(char *buf, int cs)
{
	int		ret;
	char	buf4[1024];
	int		r;
	char	**tab;

	tab = ft_strsplit(buf, ' ');
	if (test(cs, tab) == -1)
		return (0);
	if ((ret = open(tab[1], O_RDWR | O_CREAT | O_EXCL, 00777)) != -1)
		while ((r = read(cs, buf4, 1023)) > 0)
		{
			if (ft_strcmp(buf4, "") == 0)
			{
				close(ret);
				return (1);
			}
			write(ret, buf4, r);
			if (r < 1023)
			{
				close(ret);
				return (1);
			}
		}
	close(ret);
	return (0);
}
