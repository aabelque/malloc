/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 18:59:24 by aabelque          #+#    #+#             */
/*   Updated: 2017/11/30 15:45:34 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*dest;
	int		i;

	if (s && f)
	{
		if (!(dest = ft_strnew(ft_strlen(s))))
			return (NULL);
		i = 0;
		while (s[i] != '\0')
		{
			dest[i] = f(s[i]);
			i++;
		}
		return (dest);
	}
	return (NULL);
}
