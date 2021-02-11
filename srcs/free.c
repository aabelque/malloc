/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:44:25 by aabelque          #+#    #+#             */
/*   Updated: 2021/02/11 17:23:03 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int		ft_free_large(t_page **page, void *ptr)
{
	t_page		*tmp;
	t_page		*prev;

	tmp = *page;
	prev = NULL;
	if (tmp && (tmp->blk->p == ptr))
	{
		*page = tmp->nxt;
		munmap((t_page *)tmp, tmp->size);
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
	munmap((t_page *)tmp, tmp->size);
	return (0);
}

static int		ft_find_free(t_page *page, void *ptr)
{
	t_block		*blk;

	if (!page)
		return (-1);
	blk = page->blk;
	while (page)
	{
		while (blk)
		{
			if (ptr == blk->p)
			{
				blk->free = 1;
				page->rest += blk->len + STRUCT(t_block);
				return (0);
			}
			blk = blk->nxt;
		}
		page = page->nxt;
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

static void		ft_find_fragment(t_page *page)
{
	t_block		*curr;
	t_block		*prev;

	if (!page)
		return ;
	curr = page->blk;
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
	if (!ft_find_free(g_lst.tiny, ptr))
	{
		ft_find_fragment(g_lst.tiny);
		diff = STRUCT(t_page);
		ft_free_page(&g_lst.tiny, diff);
		return ;
	}
	else if (!ft_find_free(g_lst.small, ptr))
	{
		ft_find_fragment(g_lst.small);
		diff = STRUCT(t_page);
		ft_free_page(&g_lst.small, diff);
		return ;
	}
	else
		ft_free_large(&g_lst.large, ptr);
}
