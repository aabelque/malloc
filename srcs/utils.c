/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:37:31 by aabelque          #+#    #+#             */
/*   Updated: 2021/02/23 10:12:50 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		ft_free_page(t_heap **zone)
{
	t_heap	*prev;
	t_heap	*tmp;

	tmp = *zone;
	prev = NULL;
	if (tmp && !tmp->nb_blk)
	{
		*zone = tmp->nxt;
		munmap((t_heap *)tmp, tmp->size);
			return ;
	}
	while (tmp && tmp->nb_blk)
	{
		prev = tmp;
		tmp = tmp->nxt;
	}
	if (!tmp)
		return ;
	prev->nxt = tmp->nxt;
	munmap((t_heap *)tmp, tmp->size);
}

t_block			*ft_init_block(t_block *nw, t_block *blk, size_t len)
{
	blk->freed = FALSE;
	/* blk->p = (char *)blk + STRUCT(t_block); */
	if (((t_block *)((char *)blk + len + 64)) <= blk->nxt)
	{
		nw = (t_block *)((char *)blk + len);
		nw->freed = TRUE;
		nw->nxt = blk->nxt;
		nw->prv = blk;
		blk->nxt = nw;
		nw->len = (long)nw->nxt - (long)nw;
	}
	return (blk);
}

void		*ft_alloc_large(t_heap **lst, size_t len, int sz_struct)
{
	t_heap	*new;
	t_heap	*last;

	last = *lst;
	if (!(new = (t_heap *)mmap(0, len + sz_struct, PROT, FLGS, -1, 0)))
		return (NULL);
	new->nxt = NULL;
	new->size = len + sz_struct;
	new->free_size = 0;
	new->freed = FALSE;
	new->nb_blk++;
	/* new->blk = (t_block *)((char *)new + STRUCT(t_heap)); */
	new->blk = HEAP_SHIFT(new);
	new->blk->freed = FALSE;
	new->blk->len = len;
	/* new->blk->p = (void *)((char *)new->blk + STRUCT(t_block)); */
	new->blk->nxt = NULL;
	new->blk->prv = NULL;
	if (last)
	{
		while (last->nxt)
			last = last->nxt;
		last->nxt = new;
		return (BLK_SHIFT(new->blk));
	}
	*lst = new;
	return (BLK_SHIFT((*lst)->blk));
}

void		*ft_create_zone(t_heap **lst, size_t size, size_t len)
{
	t_heap	*new;
	t_heap	*last;

	last = *lst;
	if (!(new = (t_heap *)mmap(0, size, PROT, FLGS, -1, 0)))
		return (NULL);
	new->nxt = NULL;
	new->free_size = size - (sizeof(t_heap) + sizeof(t_block) + len);
	new->size = size;
	new->freed = TRUE;
	new->nb_blk++;
	new->blk = HEAP_SHIFT(new);
	new->blk->len = len;
	new->blk->freed = FALSE;
	/* new->blk->p = (void *)((char *)new->blk + STRUCT(t_block)); */
	new->blk->nxt = NULL;
	if (last)
	{
		while (last->nxt)
			last = last->nxt;
		last->nxt = new;
		return (new);
	}
	return (new);
}

size_t		ft_getalign(size_t size, int align)
{
	if (size % align)
		return (align * (size / align + 1));
	return (size != 0 ? size : align);
}
