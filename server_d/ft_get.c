/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdurr <sdurr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/02 09:57:12 by sdurr             #+#    #+#             */
/*   Updated: 2015/09/03 13:54:43 by sdurr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void		ft_get(char *buf, int cs)
{
	int		ret;
	char	buf3[1024];
	char	**tab;
	int		r;

	tab = ft_strsplit(buf, ' ');
	if ((ret = open(tab[1], O_RDONLY)) > 0)
	{
		while ((r = read(ret, buf3, 1023)) > 0)
		{
			buf3[r] = 0;
			send(cs, buf3, r + 1, MSG_OOB);
		}
		send(cs, "", 0, MSG_OOB);
		close(ret);
	}
}
