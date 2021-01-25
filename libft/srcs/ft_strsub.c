/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 11:58:25 by aabelque          #+#    #+#             */
/*   Updated: 2017/11/27 17:31:13 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *dest;

	if (!s)
		return (NULL);
	if (!(dest = (char*)malloc(sizeof(*s) * (len + 1))))
		return (NULL);
	ft_strncpy(dest, &(s[start]), len);
	dest[len] = '\0';
	return (dest);
}
