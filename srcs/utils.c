/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:37:31 by aabelque          #+#    #+#             */
/*   Updated: 2021/03/01 19:12:11 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*increase_large_heap(t_heap **lst, size_t len, int sz_struct)
{
	t_heap	*new;
	t_heap	*last;

	last = *lst;
	if (!(new = (t_heap *)mmap(0, len + sz_struct, PROT, FLGS, -1, 0)))
		return (NULL);
	new->nxt = NULL;
	new->size = len + sz_struct;
	new->free = 0;
	if (last)
	{
		while (last->nxt)
			last = last->nxt;
		last->nxt = new;
		return ((void *)HEAP_SHIFT(new));
	}
	*lst = new;
	return ((void *)HEAP_SHIFT((*lst)));
}

t_heap		**find_heap(void *ptr, t_heap **current)
{
	*current = g_lst.tiny;
	while (*current)
	{
		if (ptr == HEAP_SHIFT(*current))
			return (&g_lst.tiny);
		*current = (*current)->nxt;
	}
	*current = g_lst.small;
	while (*current)
	{
		if (ptr == HEAP_SHIFT(*current))
			return (&g_lst.small);
		*current = (*current)->nxt;
	}
	*current = g_lst.large;
	while (*current)
	{
		if (ptr == HEAP_SHIFT(*current))
			return (&g_lst.large);
		*current = (*current)->nxt;
	}
	return (NULL);
}

void		free_heap(t_heap **heap, t_heap *del)
{
	t_heap	*prev;
	t_heap	*next;

	prev = del->prv;
	next = del->nxt;
	if (prev)
	{
		prev->nxt = next;
		if (next)
			next->prv = prev;
	}
	else
	{
		*heap = (*heap)->nxt;
		if (*heap)
			(*heap)->prv = NULL;
	}
	munmap((t_heap *)del, del->size + HEADER);
}

void		*increase_heap(t_heap *last, size_t size_heap, size_t size)
{
	t_heap	*new;

	size_heap = ft_getalign(size_heap, PS);
	if (!(new = (t_heap *)mmap(0, size_heap, PROT, FLGS, -1, 0)))
		return (NULL);
	new->free = 0;
	new->size = size;
	new->nb_heap = !last ? 0 : last->nb_heap + 1;
	new->prv = last;
	new->nxt = (t_heap *)((char *)new + HEADER + size);
	new->nxt->free = 1;
	new->nxt->size = size_heap - (2 * HEADER + size);
	new->nxt->nb_heap = new->nb_heap;
	new->nxt->nxt = NULL;
	new->nxt->prv = new;
	if (last)
	{
		last->nxt = new;
		new->prv = last;
	}
	return (new);
}

size_t		ft_getalign(size_t size, int align)
{
	if (size % align)
		return (size + align - (size % align));
	return (size != 0 ? size : align);
}
