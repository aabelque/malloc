/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:37:31 by aabelque          #+#    #+#             */
/*   Updated: 2021/02/23 14:10:38 by aabelque         ###   ########.fr       */
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

void			*ft_init_block(t_block *nw, t_block *blk, size_t len)
{
	blk->freed = 0;
	/* blk->p = (char *)blk + STRUCT(t_block); */
	if (((t_block *)((char *)blk + len + 64)) <= blk->nxt)
	{
		nw = (t_block *)((char *)blk + len);
		nw->freed = 1;
		nw->nxt = blk->nxt;
		nw->prv = blk;
		blk->nxt = nw;
		nw->len = (long)nw->nxt - (long)nw;
	}
	return ((char *)blk);
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
	new->freed = 0;
	new->nb_blk++;
	/* new->blk = (t_block *)((char *)new + STRUCT(t_heap)); */
	new->blk = (t_block *)HEAP_SHIFT(new);
	new->blk->freed = 0;
	new->blk->len = len;
	/* new->blk->p = (void *)((char *)new->blk + STRUCT(t_block)); */
	new->blk->nxt = NULL;
	new->blk->prv = NULL;
	if (last)
	{
		while (last->nxt)
			last = last->nxt;
		last->nxt = new;
		return ((char *)BLK_SHIFT(new->blk));
	}
	*lst = new;
	return ((char *)BLK_SHIFT((*lst)->blk));
}

void		*ft_create_zone(t_heap **lst, size_t size, size_t len)
{
	t_heap	*new;
	t_heap	*last;

	last = *lst;
	if (!(new = (t_heap *)mmap(0, size, PROT, FLGS, -1, 0)))
		return (NULL);
	new->nxt = NULL;
	new->free_size = size - (STRUCT(t_heap) + STRUCT(t_block) + len);
	new->size = size;
	new->freed = 1;
	new->nb_blk++;
	new->blk = (t_block *)HEAP_SHIFT(new);
	new->blk->len = len;
	new->blk->freed = 0;
	/* new->blk->p = (void *)((char *)new->blk + STRUCT(t_block)); */
	new->blk->nxt = NULL;
	if (last)
	{
		while (last->nxt)
			last = last->nxt;
		last->nxt = new;
		return ((char *)new);
	}
	return ((char *)new);
}

size_t		ft_getalign(size_t size, int align)
{
	if (size % align)
		return (align * (size / align + 1));
	return (size != 0 ? size : align);
}
