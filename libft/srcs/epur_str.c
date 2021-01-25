/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epur_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 11:34:58 by aabelque          #+#    #+#             */
/*   Updated: 2021/01/11 10:26:04 by azziz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	epur_str(char *str)
{
    int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			while (str[i] && str[i + 1] &&
					(str[i + 1] == ' ' || str[i + 1] == '\t'))
				i++;
			if (!str[i + 1])
				break ;
			ft_putchar(' ');
		}
		else if (str[i])
			ft_putchar(str[i]);
		i++;
	}
	ft_putchar('\n');
}
