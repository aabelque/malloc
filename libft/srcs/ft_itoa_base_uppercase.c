/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_uppercase.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 17:52:29 by aabelque          #+#    #+#             */
/*   Updated: 2021/01/22 19:36:26 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_abs(int val)
{
	return (val < 0 ? -val : val);
}

static	void	ft_aux(int val, int base, char *str, int *i)
{
	char		*tab;

	tab = "0123456789ABCDEF";
	if (val <= -base || base <= val)
		ft_aux(val / base, base, str, i);
	str[(*i)++] = tab[ft_abs(val % base)];
}

char			*ft_itoa_base_uppercase(int val, int base)
{
	char		*str;
	int			i;

	if (base < 2 || base > 16 ||
			!(str = (char *)malloc(sizeof(char) * (sizeof(int) * 8 + 1))))
		return (NULL);
	i = 0;
	if (val < 0)
		str[i++] = '-';
	ft_aux(val, base, str, &i);
	str[i] = '\0';
	return (str);
}
