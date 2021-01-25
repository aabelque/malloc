/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 17:57:17 by aabelque          #+#    #+#             */
/*   Updated: 2021/01/22 19:39:17 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	unsigned int		ft_abs(unsigned int val)
{
	return (val < 0 ? -val : val);
}

static	void	            ft_aux(unsigned int val,
        unsigned int base, char *str, int *i)
{
	char		*tab;

	tab = "0123456789ABCDEF";
	if (val <= -base || base <= val)
		ft_aux(val / base, base, str, i);
	str[(*i)++] = tab[ft_abs(val % base)];
}

char			            *ft_utoa_base(unsigned int val,
        unsigned int base)
{
	char		*str;
	int			i;

	if (base < 2 || base > 16 ||
			!(str = (char *)malloc(sizeof(char) * (sizeof(unsigned int) * 8 + 1))))
		return (NULL);
	i = 0;
	if (val < 0)
		str[i++] = '-';
	ft_aux(val, base, str, &i);
	str[i] = '\0';
	return (str);
}
