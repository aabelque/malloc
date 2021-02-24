/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:15:13 by aabelque          #+#    #+#             */
/*   Updated: 2021/02/24 15:56:38 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*ft_find_ptr(t_heap **zone, void *ptr, size_t len)
{
	void	*new;
	t_heap	*tmp;
	t_block	*blk;

	if (!(*zone))
		return (NULL);
	new = NULL;
	tmp = *zone;
	while (tmp)
	{
		blk = tmp->blk;
		while (blk)
		{
			if (ptr == BLK_SHIFT(blk))
			{
				if (len <= blk->len)
					return (ptr);
				new = malloc(len);
				ft_memcpy(new, ptr, STRUCT(len));
				free(ptr);
				return (new);
			}
			blk = blk->nxt;
		}
		tmp->blk = blk;
		tmp = tmp->nxt;
	}
	return (new);
}

static void		*ft_find_zone(void *p, size_t size)
{
	while (g_lst.tiny)
	{
		if ((char *)p > (char *)g_lst.tiny && (char *)p < (char *)g_lst.tiny
				+ g_lst.tiny->size)
			return (ft_find_ptr(&g_lst.tiny, p, size));
		g_lst.tiny = g_lst.tiny->nxt;
	}
	while (g_lst.small)
	{
		if ((char *)p > (char *)g_lst.small && (char *)p < (char *)g_lst.small
				+ g_lst.small->size)
			return (ft_find_ptr(&g_lst.small, p, size));
		g_lst.small = g_lst.small->nxt;
	}
	while (g_lst.large)
	{
		if ((char *)p > (char *)g_lst.large && (char *)p < (char *)g_lst.large
				+ g_lst.large->size)
			return (ft_find_ptr(&g_lst.large, p, size));
		g_lst.large = g_lst.large->nxt;
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
