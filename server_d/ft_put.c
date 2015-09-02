/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdurr <sdurr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/02 10:03:06 by sdurr             #+#    #+#             */
/*   Updated: 2015/09/02 10:57:10 by sdurr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void		ft_put(char *buf, int cs)
{
	int		ret;
	char	buf4[1024];
	int		r;
	char	**tab;

	tab = ft_strsplit(buf, ' ');
	if ((ret = open(tab[1], O_RDWR | O_CREAT | O_EXCL, 00777)) == -1)
		send(cs, "ERROR this file already exist\n", 31, MSG_OOB);
	else
		send(cs, "SUCCESS\n", 9, MSG_OOB);
	while ((r = read(cs, buf4, 1023)) > 0)
	{
		buf4[r] = 0;
		if (ft_strcmp(buf4, "") == 0)
			break ;
		write(ret, buf4, r);
		if (r < 1023)
			break ;
	}
	close(ret);
}
