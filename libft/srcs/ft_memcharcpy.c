/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcharcpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:03:06 by aabelque          #+#    #+#             */
/*   Updated: 2019/10/23 16:11:13 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcharcpy(void *dest, const char c, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = (char)c;
		i++;
	}
	return (dest);
}
