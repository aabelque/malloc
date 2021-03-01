/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azziz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:27:42 by azziz             #+#    #+#             */
/*   Updated: 2021/03/01 19:34:32 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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
		*heap = increase_heap(*heap, size_heap, size);
		return ((void *)HEAP_SHIFT((*heap)));
	}
	blk = *heap;
	while (blk)
	{
		if (blk->free)
		{
			if (size <= blk->size)
			{
				create_block(blk, size);
				return ((void *)HEAP_SHIFT(blk));
			}
		}
		last = blk;
		blk = blk->nxt;
	}
	new = increase_heap(last, size_heap, size);
	return ((void *)HEAP_SHIFT(new));
}

void				*alloc(size_t size)
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

void				mutex_init(void)
{
	static int		init = 0;

	if (!init)
	{
		pthread_mutex_init(&g_thread, NULL);
		init++;
	}
	pthread_mutex_lock(&g_thread);
}

void				*malloc(size_t size)
{
	static int		init = 0;
	void			*p;

	mutex_init();
	p = NULL;
	if ((int)size < 0)
	{
		pthread_mutex_unlock(&g_thread);
		return (NULL);
	}
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
	pthread_mutex_unlock(&g_thread);
	return (p);
}
