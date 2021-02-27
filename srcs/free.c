/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:44:25 by aabelque          #+#    #+#             */
/*   Updated: 2021/02/27 16:18:56 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int		free_large_heap(t_heap **heap, void *ptr)
{
	t_heap		*tmp;
	t_heap		*prev;

	tmp = *heap;
	prev = NULL;
	if (tmp && !tmp->nxt)
		return (0);
	if (tmp && (HEAP_SHIFT(tmp) == ptr))
	{
		*heap = tmp->nxt;
		munmap((t_heap *)tmp, tmp->size + HEADER);
		{
			tmp = NULL;
			return (0);
		}
	}
	while (tmp && (HEAP_SHIFT(tmp) != ptr))
	{
		prev = tmp;
		tmp = tmp->nxt;
	}
	if (!tmp)
		return (-1);
	prev->nxt = tmp->nxt;
	munmap((t_heap *)tmp, tmp->size + HEADER);
	return (0);
}

static void		defrag_heap(t_heap **heap)
{
	t_heap		*prev;
	t_heap		*next;

	prev = (*heap)->prv;
	next = (*heap)->nxt;
	if (prev && prev->free && (prev->nb_heap == (*heap)->nb_heap))
	{
		prev->size += (*heap)->size + HEADER;
		prev->nxt = next;
		if (next)
			next->prv = prev;
		*heap = prev;
	}
	if (next && next->free && (next->nb_heap == (*heap)->nb_heap))
	{
		(*heap)->size += next->size + HEADER;
		next = next->nxt;
		(*heap)->nxt = next;
		if (next)
			next->prv = *heap;
	}
}

static int		free_block(t_heap **heap, void *ptr)
{
	t_heap		*tmp;

	if (!*heap)
		return (-1);
	tmp = *heap;
	while (tmp)
	{
		if (ptr == HEAP_SHIFT(tmp))
		{
			tmp->free = 1;
			return (0);
		}
		tmp = tmp->nxt;
	}
	return (-1);
}

void			free(void *ptr)
{
	t_heap		**heap;
	t_heap		*current;

	if (!ptr)
		return ;
	if ((heap = find_heap(ptr, &current)))
	{
		free_block(heap, ptr);
		defrag_heap(&current);
		if (release_heap(current))
			free_heap(heap, current);
	}
	else
		free_large_heap(&g_lst.large, ptr);
}
