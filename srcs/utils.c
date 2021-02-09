/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:37:31 by aabelque          #+#    #+#             */
/*   Updated: 2021/02/09 09:56:19 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		ft_can_i_free(t_page **zone)
{
	t_page	*prev;
	t_page	*curr;

	curr = *zone;
	prev = NULL;
	while (curr)
	{
		if (curr->rest == curr->size)
		{
			if (prev)
				prev->nxt = curr->nxt;
			if (!(munmap(curr, curr->size + STRUCT(t_page))))
			{
				curr = NULL;
				return ;
			}
		}
		prev = curr;
		curr = curr->nxt;
	}
}

void		ft_init_block(t_block **nw, t_block **blk, size_t len)
{
	(*blk)->free = 0;
	(*blk)->p = (void *)(*blk) + STRUCT(t_block);
	if (((void *)(*blk) + len + 64) <= (void *)(*blk)->nxt)
	{
		(*nw) = (void*)(*blk) + len;
		(*nw)->free = 1;
		(*nw)->nxt = (void*)(*blk)->nxt;
		(*nw)->prv = (void*)(*blk);
		(*blk)->nxt = (void*)(*nw);
		(*nw)->len = (long)(*nw)->nxt - (long)(*nw);
	}
}

void		*ft_alloc_large(t_page **page, size_t len)
{
	t_page	*new;

	if (!(new = (t_page *)mmap(0, len, PROT, FLGS, -1, 0)))
		return (NULL);
	new->nxt = NULL;
	new->size = len;
	new->rest = 0;
	new->free = 0;
	new->blk = (void *)new + STRUCT(t_page);
	new->blk->free = 0;
	new->blk->len = len;
	new->blk->p = (void *)new->blk + STRUCT(t_block);
	new->blk->nxt = (void *)new->blk->p + len;
	new->blk->prv = (void *)new->blk;
	if (*page)
	{
		while ((*page)->nxt)
			*page = (*page)->nxt;
		(*page)->nxt = (void *)new;
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
	new->rest = size - (STRUCT(t_page) + STRUCT(t_block));
	new->size = size;
	new->free = 1;
	new->blk = (void *)new + STRUCT(t_page);
	new->blk->len = len;
	new->blk->free = 0;
	new->blk->p = (void *)new->blk + STRUCT(t_block);
	new->blk->nxt = NULL;
	if (prev)
		prev->nxt = (void *)new;
	return ((void *)new);
}

size_t		ft_getalign(size_t size, int align)
{
	if (size % align)
		return (size + align - (size % align));
	return (size != 0 ? size : align);
}
