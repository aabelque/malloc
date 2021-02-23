/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:44:25 by aabelque          #+#    #+#             */
/*   Updated: 2021/02/23 10:11:52 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int		ft_free_large(t_heap **page, void *ptr)
{
	t_heap		*tmp;
	t_heap		*prev;

	if (!*page)
		return (-1);
	tmp = *page;
	prev = NULL;
	if (tmp && (BLK_SHIFT(tmp->blk) == ptr))
	{
		*page = tmp->nxt;
		munmap((t_heap *)tmp, tmp->size);
		{
			tmp = NULL;
			return (0);
		}
	}
	while (tmp && (BLK_SHIFT(tmp->blk) != ptr))
	{
		prev = tmp;
		tmp = tmp->nxt;
	}
	if (!tmp)
		return (-1);
	prev->nxt = tmp->nxt;
	munmap((t_heap *)tmp, tmp->size);
	return (0);
}

static int		ft_find_free(t_heap **page, void *ptr)
{
	t_heap		*tmp;
	t_block		*blk;

	if (!*page)
		return (-1);
	tmp = *page;
	while (tmp)
	{
		blk = tmp->blk;
		while (blk)
		{
			if (ptr == BLK_SHIFT(blk))
			{
				blk->freed = TRUE;
				tmp->free_size += blk->len + STRUCT(t_block);
				tmp->nb_blk--;
				return (0);
			}
			blk = blk->nxt;
		}
		tmp = tmp->nxt;
	}
	return (-1);
}

static void		ft_defrag(t_block **curr, t_block **prev)
{
	if ((*prev)->freed && (*prev != *curr))
	{
		(*prev)->nxt = (*curr)->nxt;
		(*curr)->prv = (*prev)->prv;
		*curr = *prev;
		(*curr)->len = (long)(*curr)->nxt - (long)*curr;
	}
}

static void		ft_find_fragment(t_heap *page)
{
	t_block		*curr;
	t_block		*prev;

	if (!page)
		return ;
	curr = page->blk;
	prev = curr;
	while (curr)
	{
		if (curr->freed && prev)
			if (prev->freed)
				ft_defrag(&curr, &prev);
		prev = curr;
		curr = curr->nxt;
	}
}

void			free(void *ptr)
{
	/* int			diff; */

	if (!ptr)
		return ;
	if (!ft_find_free(&g_lst.tiny, ptr))
	{
		/* ft_find_fragment(g_lst.tiny); */
		/* diff = STRUCT(t_heap); */
		ft_free_page(&g_lst.tiny);
		return ;
	}
	else if (!ft_find_free(&g_lst.small, ptr))
	{
		/* ft_find_fragment(g_lst.small); */
		/* diff = STRUCT(t_heap); */
		ft_free_page(&g_lst.small);
		return ;
	}
	else
		ft_free_large(&g_lst.large, ptr);
}
