/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdurr <sdurr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/02 10:57:31 by sdurr             #+#    #+#             */
/*   Updated: 2015/09/02 11:00:43 by sdurr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void				ft_ls(int cs)
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
