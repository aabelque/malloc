/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:07:17 by aabelque          #+#    #+#             */
/*   Updated: 2021/01/22 19:42:39 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	long long		ft_abs(long long val)
{
	return (val < 0 ? -val : val);
}

static	void	        ft_aux(long long val, int base, char *str, int *i)
{
	char		*tab;

	tab = "0123456789abcdef";
	if (val <= -base || base <= val)
		ft_aux(val / base, base, str, i);
	str[(*i)++] = tab[ft_abs(val % base)];
}

char			        *ft_lltoa_base(long long val, int base)
{
	char		*str;
	int			i;

	if (base < 2 || base > 16 ||
			!(str = (char *)malloc(sizeof(char)
			        * (sizeof(long long) * 8 + 1))))
		return (NULL);
	i = 0;
	if (val < 0)
		str[i++] = '-';
	ft_aux(val, base, str, &i);
	str[i] = '\0';
	return (str);
}
