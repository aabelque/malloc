/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:15:13 by aabelque          #+#    #+#             */
/*   Updated: 2021/02/27 16:49:47 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*ft_find_ptr(t_heap **zone, void *ptr, size_t len)
{
	void	*new;
	t_heap	*tmp;

	if (!(*zone))
		return (NULL);
	new = NULL;
	tmp = *zone;
	while (tmp)
	{
		if (ptr == HEAP_SHIFT(tmp))
		{
			if (len <= tmp->size)
				return (ptr);
			new = malloc(len);
			ft_memcpy(new, ptr, tmp->size);
			free(ptr);
			return (new);
		}
		tmp = tmp->nxt;
	}
	return (new);
}

static void		*ft_find_zone(void *p, size_t size)
{
	t_heap		*heap;

	heap = g_lst.tiny;
	while (heap)
	{
		if (p == HEAP_SHIFT(heap))
			return (ft_find_ptr(&g_lst.tiny, p, size));
		heap = heap->nxt;
	}
	heap = g_lst.small;
	while (heap)
	{
		if (p == HEAP_SHIFT(heap))
			return (ft_find_ptr(&g_lst.small, p, size));
		heap = heap->nxt;
	}
	heap = g_lst.large;
	while (heap)
	{
		if (p == HEAP_SHIFT(heap))
			return (ft_find_ptr(&g_lst.large, p, size));
		heap = heap->nxt;
	}
	return (NULL);
}

void			*realloc(void *ptr, size_t size)
{
	void	*p;
	size_t	align;

	if ((int)size < 0)
		return (NULL);
	if (!ptr)
		return (malloc(size));
	else if (!size)
	{
		free(ptr);
		return (malloc(16));
	}
	align = ft_getalign(size, 16);
	p = ft_find_zone(ptr, align);
	return (p);
}

void			*reallocf(void *ptr, size_t size)
{
	void	*p;

	if (!(p = realloc(ptr, size)))
		free(ptr);
	return (p);
}
