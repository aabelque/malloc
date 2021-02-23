/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azziz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:27:42 by azziz             #+#    #+#             */
/*   Updated: 2021/02/23 14:11:00 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void			*ft_newblock(t_block *new, t_block *blk, size_t sz,
		t_heap **page)
{
	new = (t_block *)((char *)BLK_SHIFT(blk) + blk->len);
	new->len = sz;
	new->freed = 0;
	/* new->p = (char *)new + STRUCT(t_block); */
	new->nxt = NULL;
	new->prv = blk;
	blk->nxt = new;
	(*page)->free_size -= (sz + STRUCT(t_block));
	(*page)->nb_blk++;
	if (!(*page)->free_size)
		(*page)->freed = 0;
	return ((char *)BLK_SHIFT(new));
}

void				*ft_findblock(t_heap **page, size_t sz)
{
	t_block			*blk;
	t_block			*last;
	t_block			*new;

	blk = (*page)->blk;
	last = blk;
	new = NULL;
	while (blk)
	{
		if (blk->freed && (sz + STRUCT(t_block)) <= blk->len)
		{
			blk = ft_init_block(new, blk, sz + STRUCT(t_block));
			blk->len = sz;
			(*page)->free_size -= sz + STRUCT(t_block);
			(*page)->nb_blk++;
			return ((char *)blk);
		}
		last = blk;
		blk = blk->nxt;
	}
	return(ft_newblock(new, last, sz, page));
}

static void			*ft_getblock(t_heap **zone, size_t len, size_t len_zone)
{
	t_heap			*page;
	t_block			*new;

	if (!*zone)
	{
		*zone = (t_heap *)ft_create_zone(zone, len_zone, len);
		return ((char *)BLK_SHIFT((*zone)->blk));
	}
	page = *zone;
	while (page)
	{
		if (page->freed)
		{
			if ((len + STRUCT(t_block)) <= page->free_size)
				if ((new = ft_findblock(&page, len)))
					return ((char *)BLK_SHIFT(new));
		}
		page = page->nxt;
	}
	page = (t_heap *)ft_create_zone(zone, len_zone, len);
	return ((char *)BLK_SHIFT(page->blk));
}

static void			*ft_alloc(size_t size)
{
	struct rlimit	rlp;
	size_t			align;

	getrlimit(RLIMIT_DATA, &rlp);
	align = ft_getalign(size, 16);
	if (align > rlp.rlim_cur || size > rlp.rlim_cur)
		return (NULL);
	if (align <= TINY)
		return (ft_getblock(&g_lst.tiny, align, TINY_ZONE));
	else if (align <= SMALL)
		return (ft_getblock(&g_lst.small, align, SMALL_ZONE));
	else
		return (ft_alloc_large(&g_lst.large, align, STRUCT(t_heap) + STRUCT(t_block)));
	return (NULL);
}

void				*malloc(size_t size)
{
	static int		init = 0;
	void			*p;

	p = NULL;
	if ((int)size < 0)
		return (NULL);
	if (!size)
		size = 16;
	if (!init)
	{
		g_lst.tiny = NULL;
		g_lst.small = NULL;
		g_lst.large = NULL;
		init++;
	}
	p = ft_alloc(size);
	return (p);
}
