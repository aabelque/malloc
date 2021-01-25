/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 21:04:21 by aabelque          #+#    #+#             */
/*   Updated: 2017/11/30 15:46:21 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
			dest[i] = f(i, s[i]);
			i++;
		}
		return (dest);
	}
	return (NULL);
}
