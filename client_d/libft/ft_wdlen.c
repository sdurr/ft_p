/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wdlen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: getrembl <getrembl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 18:20:10 by getrembl          #+#    #+#             */
/*   Updated: 2015/04/11 19:06:21 by getrembl         ###   ########.fr       */
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
