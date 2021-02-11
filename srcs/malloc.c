/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azziz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:27:42 by azziz             #+#    #+#             */
/*   Updated: 2021/02/11 14:29:18 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block			*ft_newblock(t_block *new, t_block *blk, size_t sz,
		t_page **page)
{
	new = (void *)blk->p + blk->len;
	new->len = sz;
	new->free = 0;
	new->p = (char *)new + STRUCT(t_block);
	new->nxt = NULL;
	new->prv = blk;
	blk->nxt = new;
	(*page)->rest -= sz + STRUCT(t_block);
	if (!(*page)->rest)
		(*page)->free = 0;
	return (new);
}

t_block				*ft_findblock(t_page **page, size_t sz)
{
	t_block			*blk;
	t_block			*last;
	t_block			*new;

	blk = (*page)->blk;
	last = blk;
	new = NULL;
	while (blk)
	{
		if (blk->free && (sz + STRUCT(t_block)) <= blk->len)
		{
			blk = ft_init_block(new, blk, sz + STRUCT(t_block));
			blk->len = sz;
			(*page)->rest -= sz + STRUCT(t_block);
			return (blk);
		}
		last = blk;
		blk = blk->nxt;
	}
	return(ft_newblock(new, last, sz, page));
}

static void			*ft_getblock(t_page **zone, size_t len, size_t len_zone)
{
	t_page			*page;
	t_block			*new;

	if (!*zone)
	{
		*zone = (t_page *)ft_create_zone(*zone, len_zone, len);
		return ((*zone)->blk->p);
	}
	page = *zone;
	while (page)
	{
		if (page->free)
		{
			if ((len + STRUCT(t_block)) <= page->rest)
				if ((new = ft_findblock(&page, len)))
					return (new->p);
		}
		page = page->nxt;
	}
	page = ft_create_zone(*zone, len_zone, len);
	return (page->blk->p);
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
		return (ft_alloc_large(&g_lst.large, align, STRUCT(t_page) + STRUCT(t_block)));
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
