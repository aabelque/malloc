/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 18:03:02 by aabelque          #+#    #+#             */
/*   Updated: 2019/10/18 14:38:19 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_size_number(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char			*ft_itoa(int n)
{
	char	*str;
	size_t	len;

	if (n < -2147483647)
		return (ft_strdup("-2147483648"));
	len = ft_size_number(n);
	if (!(str = (char *)malloc(sizeof(*str) * len + 1)))
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	str[len] = '\0';
	while (n >= 10)
	{
		str[len - 1] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	str[len - 1] = n + '0';
	return (str);
}
