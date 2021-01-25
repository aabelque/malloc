/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 21:18:08 by aabelque          #+#    #+#             */
/*   Updated: 2017/11/30 19:46:28 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char *tmpd;
	char *tmps;

	tmpd = (char*)dest;
	tmps = (char*)src;
	if (tmps < tmpd)
	{
		tmps = tmps + n - 1;
		tmpd = tmpd + n - 1;
		while (n > 0)
		{
			*tmpd-- = *tmps--;
			n--;
		}
	}
	else
	{
		while (n > 0)
		{
			*tmpd++ = *tmps++;
			n--;
		}
	}
	return (dest);
}
