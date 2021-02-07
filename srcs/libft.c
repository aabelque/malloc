/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 22:18:33 by aabelque          #+#    #+#             */
/*   Updated: 2021/02/07 23:20:43 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}

void		ft_putchar(char c)
{
	write(1, &c, 1);
}

void		ft_putnbr(int n)
{
	if (n < -2147483647)
	{
		ft_putstr("-2147483648");
	}
	else
	{
		if (n < 0)
		{
			ft_putchar('-');
			n = -n;
		}
		if (n <= 9)
		{
			ft_putchar(n + '0');
		}
		else
		{
			ft_putnbr(n / 10);
			ft_putnbr(n % 10);
		}
	}
}

size_t		ft_strlen(const char *s)
{
	const char	*i;

	i = s;
	while (*i)
		i++;
	return (i - s);
}

void		ft_putstr(char const *s)
{
	write(1, s, ft_strlen(s));
}
