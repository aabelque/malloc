/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azziz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:27:42 by azziz             #+#    #+#             */
/*   Updated: 2021/02/27 16:50:32 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*increase_large_heap(t_heap **lst, size_t len, int sz_struct) {
	t_heap	*new;
	t_heap	*last;

	last = *lst;
	if (!(new = (t_heap *)mmap(0, len + sz_struct, PROT, FLGS, -1, 0)))
		return (NULL);
	new->nxt = NULL;
	new->size = len + sz_struct;
	new->free = 0;
	if (last)
	{
		while (last->nxt)
			last = last->nxt;
		last->nxt = new;
		return (HEAP_SHIFT(new));
	}
	*lst = new;
	return (HEAP_SHIFT((*lst)));
}

void				create_block(t_heap *blk, size_t size)
{
	t_heap			*new;

	blk->free = 0;
	if (blk->size < size + HEADER + 16)
		return ;
	new = (void *)((char *)blk + HEADER + size);
	new->free = 1;
	new->size = blk->size - (HEADER + size);
	blk->size = size;
	new->nb_heap = blk->nb_heap;
	new->nxt = blk->nxt;
	new->prv = blk;
	if (blk->nxt)
		blk->nxt->prv = new;
	blk->nxt = new;
}

static void			*getblock(t_heap **heap, size_t size, size_t size_heap)
{
	t_heap			*blk;
	t_heap			*new;
	t_heap			*last;

	if (!*heap)
	{
		*heap = (t_heap *)increase_heap(*heap, size_heap, size);
		return (HEAP_SHIFT((*heap)));
	}
	blk = *heap;
	new = NULL;
	last = NULL;
	while (blk)
	{
		if (blk->free)
		{
			if ((size + HEADER) <= blk->size)
			{
				create_block(blk, size);
				return (HEAP_SHIFT(blk));
			}
		}
		last = blk;
		blk = blk->nxt;
	}
	new = (t_heap *)increase_heap(last, size_heap, size);
	return (HEAP_SHIFT(new));
}

static void			*alloc(size_t size)
{
	size_t			align;
	struct rlimit	rlp;

	getrlimit(RLIMIT_DATA, &rlp);
	align = ft_getalign(size, 16);
	if (align > rlp.rlim_cur || size > rlp.rlim_cur)
		return (NULL);
	if (align <= TINY)
		return (getblock(&g_lst.tiny, align, TINY_ZONE));
	else if (align <= SMALL)
		return (getblock(&g_lst.small, align, SMALL_ZONE));
	else
		return (increase_large_heap(&g_lst.large, align, HEADER));
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
	p = alloc(size);
	return (p);
}
