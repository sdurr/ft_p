/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdurr <sdurr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/09 17:42:01 by sdurr             #+#    #+#             */
/*   Updated: 2015/06/09 17:42:02 by sdurr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

static int			bufatbackn(char **line, char **bkp, char **buffer, int *i)
{
	if (!(*line = ft_strdup(*bkp)))
		return (-1);
	ft_strdel(&*bkp);
	ft_strdel(&*buffer);
	if (i[0] == 0 || i[0] == EOF)
		return (0);
	return (1);
}

int					get_next_line(int const fd, char **line)
{
	int				i[2];
	char			*buffer;
	static char		*bkp = NULL;

	i[0] = 0;
	i[1] = 0;
	if (fd < 0 || !line || BUFF_SIZE < 1 || !*line)
		return (-1);
	while (i[1] < BUFF_SIZE)
	{
		if (!bkp)
			bkp = ft_strnew(2);
		buffer = ft_strnew(2);
		if ((i[0] = read(fd, buffer, 1)) < 0)
			return (-1);
		if (*buffer != '\n' && (i[0] != 0 || i[0] != EOF))
			bkp = ft_strjoin(bkp, buffer);
		if (*buffer == '\n' || i[0] == 0 || i[0] == EOF)
			return (bufatbackn(line, &bkp, &buffer, i));
		i[1]++;
	}
	if (i[1] == BUFF_SIZE)
		return (get_next_line(fd, line));
	return (-1);
}

/*
**    In the function get_next_line, i[0] is ret of syscall read,
**    i[1] is principal index.
*/
