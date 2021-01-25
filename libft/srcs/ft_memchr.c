/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 11:38:25 by aabelque          #+#    #+#             */
/*   Updated: 2017/11/24 17:39:40 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	void	*tmp;

	i = 0;
	tmp = (unsigned char*)s;
	while (i < n)
	{
		if (((unsigned char *)tmp)[i] == (unsigned char)c)
			return (tmp + i);
		i++;
	}
	tmp = NULL;
	return (tmp);
}
