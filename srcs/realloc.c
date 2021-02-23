/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:15:13 by aabelque          #+#    #+#             */
/*   Updated: 2021/02/23 10:05:36 by aabelque         ###   ########.fr       */
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
		/* ft_hexdump((long)tmp); */
		/* write(1, "\n", 1); */
		blk = tmp->blk;
		while (blk)
		{
			if (ptr == BLK_SHIFT(blk))
			{
				if (len <= blk->len)
					return (ptr);
				new = malloc(len);
				ft_memcpy(new, ptr, len);
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
	t_heap	*tiny;
	t_heap	*small;
	t_heap	*large;

	tiny = g_lst.tiny;
	small = g_lst.small;
	large = g_lst.large;
	while (tiny)
	{
		if ((char *)p > (char *)tiny && (char *)p < (char *)tiny
				+ tiny->size)
			return (ft_find_ptr(&tiny, p, size));
		tiny = tiny->nxt;
	}
	while (small)
	{
		if ((char *)p > (char *)small && (char *)p < (char *)small
				+ small->size)
			return (ft_find_ptr(&small, p, size));
		small = small->nxt;
	}
	while (large)
	{
		if ((char *)p > (char *)large && (char *)p < (char *)large
				+ large->size)
			return (ft_find_ptr(&large, p, size));
		large = large->nxt;
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
	align = ft_getalign(size, 15);
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
