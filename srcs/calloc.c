/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 23:23:50 by aabelque          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/02/23 13:48:34 by aabelque         ###   ########.fr       */
=======
/*   Updated: 2021/02/24 16:12:23 by aabelque         ###   ########.fr       */
>>>>>>> refact
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
<<<<<<< HEAD
	void *p;
	size_t len;
=======
	void	*p;
	size_t	len;
>>>>>>> refact

	len = ft_getalign(count * size, 16);
	if (!(p = malloc(len)))
		return (NULL);
	ft_bzero(p, len);
	return (p);
}
