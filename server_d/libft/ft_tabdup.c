/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdurr <sdurr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/09 17:41:39 by sdurr             #+#    #+#             */
/*   Updated: 2015/06/09 17:41:40 by sdurr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		**ft_tabdup(char const **tab)
{
	char	**ret;
	int		i;

	i = -1;
	if (!(ret = (char **)malloc(sizeof(char *) * (ft_tablen((char**)tab) + 1))))
		return (NULL);
	while (tab[++i])
		if (!(ret[i] = ft_strdup(tab[i])))
			return (NULL);
	ret[i] = NULL;
	return (ret);
}
