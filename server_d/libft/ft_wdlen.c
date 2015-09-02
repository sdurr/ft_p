/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wdlen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdurr <sdurr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/09 17:41:52 by sdurr             #+#    #+#             */
/*   Updated: 2015/06/09 17:41:53 by sdurr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_wdlen(char const *s, char c, int i)
{
	size_t	len;

	len = 0;
	if (s)
		while (s[i] != c && s[i])
		{
			i++;
			len++;
		}
	return (len);
}
