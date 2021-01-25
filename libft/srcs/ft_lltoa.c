/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 18:20:49 by aabelque          #+#    #+#             */
/*   Updated: 2019/11/03 16:59:58 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	len_number(long long n)
{
	size_t	cnt;

	cnt = 0;
	if (n < 0)
	{
		n *= -1;
		cnt++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		cnt++;
	}
	return (cnt);
}

char			*ft_lltoa(long long n)
{
	char	*s;
	size_t	len;

	len = len_number(n);
	if (!(s = (char *)malloc(sizeof(*s) * len + 1)))
		return (NULL);
	if (n < 0)
	{
		s[0] = '-';
		n *= -1;
	}
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
