/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 23:23:50 by aabelque          #+#    #+#             */
/*   Updated: 2021/02/07 23:40:45 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	ft_bzero(void *p, size_t n)
{
	if (!n)
		return ;
	while ((*((char *)p++) = '\0'))
		;
}

void	*calloc(size_t count, size_t size)
{
	void *p;

	if (!(p = malloc(count * size)))
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}
