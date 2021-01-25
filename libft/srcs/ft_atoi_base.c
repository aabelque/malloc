/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 13:47:22 by aabelque          #+#    #+#             */
/*   Updated: 2021/01/22 19:36:49 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_base(char c, int str_base)
{
	if (str_base <= 10)
		return (c >= '0' && c <= '9');
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= ('a' + str_base - 10)));
}

static	int		ft_base2(char c, int str_base)
{
	if (str_base <= 10)
		return (c >= '0' && c <= '9');
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= ('A' + str_base - 10)));
}

int				ft_atoi_base(const char *str, int str_base)
{
	int			sign;
	int			value;

	value = 0;
	if (str_base <= 1 || str_base > 36)
		return (0);
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f'
			|| *str == '\r' || *str == '\v')
		str++;
	sign = (*str == '-') ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_base(*str, str_base) || ft_base2(*str, str_base))
	{
		if (*str - 'a' >= 0)
			value = value * str_base + (*str - 'a' + 10);
		else if (*str - 'A' >= 0)
			value = value * str_base + (*str - 'A' + 10);
		else
			value = value * str_base + (*str - '0');
		str++;
	}
	return (value * sign);
}
