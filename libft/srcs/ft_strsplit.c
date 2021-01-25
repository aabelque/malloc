/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 16:06:14 by aabelque          #+#    #+#             */
/*   Updated: 2017/12/02 22:15:02 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_count_word(char const *s, char c)
{
	size_t		count;
	int			i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		s++;
	}
	return (count);
}

static	int		ft_size_word(char const *s, char c)
{
	size_t		siz;
	int			i;

	i = 0;
	siz = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		siz++;
	}
	return (siz);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**tab;
	size_t		i;
	size_t		count;
	size_t		size;

	if (!s)
		return (NULL);
	count = ft_count_word(s, c);
	if (!(tab = malloc(sizeof(*tab) * (count + 1))))
		return (NULL);
	i = -1;
	while (++i < count && *s)
	{
		while (*s == c)
			s++;
		size = ft_size_word(s, c);
		if (!(tab[i] = malloc((size + 1) * sizeof(**tab))))
			return (NULL);
		ft_strncpy(tab[i], s, size);
		tab[i][size] = '\0';
		s += size;
	}
	tab[i] = NULL;
	return (tab);
}
