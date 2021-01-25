/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:39:44 by aabelque          #+#    #+#             */
/*   Updated: 2019/11/21 18:56:48 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

static	size_t	len_number(unsigned int n)
{
	size_t	cnt;

	cnt = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		cnt++;
	}
	return (cnt);
}

char			*ft_utoa(unsigned int n)
{
	char	*s;
	size_t	len;

	len = len_number(n);
	if (!(s = (char *)malloc(sizeof(*s) * len + 1)))
		return (NULL);
	s[len] = '\0';
	while (n >= 10)
	{
		s[len - 1] = n % 10 + '0';
		n /= 10;
		len--;
	}
	s[len - 1] = n + '0';
	return (s);
}
