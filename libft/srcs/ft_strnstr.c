/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 11:37:19 by aabelque          #+#    #+#             */
/*   Updated: 2017/11/28 12:51:12 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t len;

	if (*s2 == '\0')
		return ((char*)s1);
	len = ft_strlen(s2);
	while (*s1 != '\0' && n >= len)
	{
		if (ft_strncmp(s1, s2, len) == 0)
			return ((char*)s1);
		s1++;
		n--;
	}
	return (NULL);
}
