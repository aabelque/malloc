/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:44:25 by aabelque          #+#    #+#             */
/*   Updated: 2021/02/24 12:12:50 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int		ft_free_large(t_heap **heap, void *ptr)
{
	t_heap		*tmp;
	t_heap		*prev;

	tmp = *heap;
	prev = NULL;
	if (tmp && (tmp->blk->p == ptr))
	{
		*heap = tmp->nxt;
		munmap((t_heap *)tmp, tmp->size);
		{
			tmp = NULL;
			return (0);
		}
	}
	while (tmp && (tmp->blk->p != ptr))
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

static int		ft_find_free(t_heap **heap, void *ptr)
{
	t_heap		*tmp;
	t_block		*blk;

	if (!*heap)
		return (-1);
	tmp = *heap;
	while (tmp)
	{
		blk = tmp->blk;
		while (blk)
		{
			if (ptr == blk->p)
			{
				blk->free = 1;
				tmp->rest += blk->len + STRUCT(t_block);
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
	if ((*prev)->free && (*prev != *curr))
	{
		(*prev)->nxt = (*curr)->nxt;
		(*curr)->prv = (*prev)->prv;
		*curr = *prev;
		(*curr)->len = (long)(*curr)->nxt - (long)*curr;
	}
}

static void		ft_find_fragment(t_heap *heap)
{
	t_block		*curr;
	t_block		*prev;

	if (!heap)
		return ;
	curr = heap->blk;
	prev = curr;
	while (curr)
	{
		if (curr->free && prev)
			if (prev->free)
				ft_defrag(&curr, &prev);
		prev = curr;
		curr = curr->nxt;
	}
}

void			free(void *ptr)
{
	int			diff;

	if (!ptr)
		return ;
	if (!ft_find_free(&g_lst.tiny, ptr))
	{
		ft_find_fragment(g_lst.tiny);
		diff = STRUCT(t_heap);
		ft_free_heap(&g_lst.tiny, diff);
		return ;
	}
	else if (!ft_find_free(&g_lst.small, ptr))
	{
		ft_find_fragment(g_lst.small);
		diff = STRUCT(t_heap);
		ft_free_heap(&g_lst.small, diff);
		return ;
	}
	else
		ft_free_large(&g_lst.large, ptr);
}
