/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:44:25 by aabelque          #+#    #+#             */
/*   Updated: 2021/03/01 19:57:34 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int				release_heap(t_heap *heap)
{
	t_heap	*prv;
	t_heap	*nxt;

	prv = heap->prv;
	nxt = heap->nxt;
	if ((!prv && !nxt))
		return (0);
	else if (!prv && nxt && (nxt->nb_heap != heap->nb_heap))
		return (1);
	else if (prv && !nxt && (prv->nb_heap != heap->nb_heap))
		return (1);
	else if (prv && nxt && (prv->nb_heap != heap->nb_heap)
			&& (nxt->nb_heap != heap->nb_heap))
		return (1);
	else
		return (0);
	return (0);
}

static void		defrag_heap(t_heap **heap)
{
	t_heap		*prev;
	t_heap		*next;

	prev = (*heap)->prv;
	next = (*heap)->nxt;
	while (prev && prev->free && (prev->nb_heap == (*heap)->nb_heap))
	{
		prev->size += (*heap)->size + HEADER;
		prev->nxt = next;
		if (next)
			next->prv = prev;
		*heap = prev;
		prev = prev->prv;
	}
	while (next && next->free && (next->nb_heap == (*heap)->nb_heap))
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

void			free_lock(void *ptr)
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
		return ;
}

void			free(void *ptr)
{
	mutex_init();
	free_lock(ptr);
	pthread_mutex_unlock(&g_thread);
}
