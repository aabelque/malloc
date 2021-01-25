/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:25:37 by aabelque          #+#    #+#             */
/*   Updated: 2017/11/30 17:42:03 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	len;
	char	*trim;

	if (!s)
		return (NULL);
	while (*s != '\0' && (*s == ' ' || *s == '\n' || *s == '\t'))
		s++;
	len = ft_strlen(s);
	while (len > 0 && (s[len - 1] == ' ' || s[len - 1] == '\n' ||
				s[len - 1] == '\t'))
		len--;
	if (!(trim = (char *)malloc(sizeof(*trim) * (len + 1))))
		return (NULL);
	ft_strcpy(trim, s);
	trim[len] = '\0';
	return (trim);
}
