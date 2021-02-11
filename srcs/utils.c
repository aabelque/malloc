/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:37:31 by aabelque          #+#    #+#             */
/*   Updated: 2021/02/11 17:22:39 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		ft_free_page(t_page **zone, int diff)
{
	t_page	*prev;
	t_page	*tmp;

	tmp = *zone;
	prev = NULL;
	if (tmp && (tmp->size == (tmp->rest + diff)))
	{
		*zone = tmp->nxt;
		munmap((t_page *)tmp, tmp->size);
			return ;
	}
	while (tmp && (tmp->size != (tmp->rest + diff)))
	{
		prev = tmp;
		tmp = tmp->nxt;
	}
	if (!tmp)
		return ;
	prev->nxt = tmp->nxt;
	munmap((t_page *)tmp, tmp->size);
}

t_block			*ft_init_block(t_block *nw, t_block *blk, size_t len)
{
	blk->free = 0;
	blk->p = (char *)blk + STRUCT(t_block);
	if ((blk + len + 64) <= blk->nxt)
	{
		nw = blk + len;
		nw->free = 1;
		nw->nxt = blk->nxt;
		nw->prv = blk;
		blk->nxt = nw;
		nw->len = (long)nw->nxt - (long)nw;
	}
	return (blk);
}

void		*ft_alloc_large(t_page **page, size_t len, int sz_struct)
{
	t_page	*new;

	if (!(new = (t_page *)mmap(0, len + sz_struct, PROT, FLGS, -1, 0)))
		return (NULL);
	new->nxt = NULL;
	new->size = len + sz_struct;
	new->rest = 0;
	new->free = 0;
	new->blk = (t_block *)new + STRUCT(t_page);
	new->blk->free = 0;
	new->blk->len = len;
	new->blk->p = (char *)new->blk + STRUCT(t_block);
	new->blk->nxt = (t_block *)new->blk->p + len;
	new->blk->prv = (t_block *)new->blk;
	if (*page)
	{
		while ((*page)->nxt)
			*page = (*page)->nxt;
		(*page)->nxt = new;
		return (new->blk->p);
	}
	*page = new;
	return ((*page)->blk->p);
}

void		*ft_create_zone(t_page *prev, size_t size, size_t len)
{
	t_page	*new;

	if (!(new = (t_page *)mmap(0, size, PROT, FLGS, -1, 0)))
		return (NULL);
	new->nxt = NULL;
	new->rest = size - (STRUCT(t_page) + STRUCT(t_block) + len);
	new->size = size;
	new->free = 1;
	new->blk = (t_block *)((char *)new + STRUCT(t_page));
	new->blk->len = len;
	new->blk->free = 0;
	new->blk->p = (char *)new->blk + STRUCT(t_block);
	new->blk->nxt = NULL;
	if (prev)
		prev->nxt = new;
	return ((void *)new);
}

size_t		ft_getalign(size_t size, int align)
{
	if (size % align)
		return (size + align - (size % align));
	return (size != 0 ? size : align);
}
