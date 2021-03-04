/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 23:23:50 by aabelque          #+#    #+#             */
/*   Updated: 2021/03/04 16:15:56 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	ft_bzero(void *p, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		((char *)p)[i] = '\0';
		i++;
	}
}

void	*calloc(size_t count, size_t size)
{
	void	*p;
	size_t	len;

	len = ft_getalign(count * size, 16);
	if (!(p = malloc(len)))
		return (NULL);
	ft_bzero(p, len);
	return (p);
}
