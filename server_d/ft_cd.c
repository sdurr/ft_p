/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdurr <sdurr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/02 10:18:24 by sdurr             #+#    #+#             */
/*   Updated: 2015/09/02 10:55:20 by sdurr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void		ft_cd(char *buf, char *pwd, int cs)
{
	char	**tab;
	int		success;

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
