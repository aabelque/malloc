/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:15:13 by aabelque          #+#    #+#             */
/*   Updated: 2021/02/07 21:59:07 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*ft_find_ptr(t_page **zone, void *ptr, size_t len)
{
	void		*new;
	t_block		*blk;

	new = NULL;
	if (!(*zone))
		return (NULL);
	blk = (*zone)->blk;
	while (*zone)
	{
		while (blk)
		{
			if (ptr == blk->p)
			{
				if (len <= blk->len)
					return (ptr);
				new = malloc(len);
				ft_memcpy(new, ptr, STRUCT(len));
				free(ptr);
				return (new);
			}
			blk = blk->nxt;
		}
		*zone = (*zone)->nxt;
	}
	return (new);
}

static void		*ft_find_zone(void *p, size_t size)
{
	while (g_lst.tiny)
	{
		if (p > (void *)g_lst.tiny && p < (void *)g_lst.tiny
				+ g_lst.tiny->size)
			return (ft_find_ptr(&g_lst.tiny, p, size));
		g_lst.tiny = g_lst.tiny->nxt;
	}
	while (g_lst.small)
	{
		if (p > (void *)g_lst.small && p < (void *)g_lst.small
				+ g_lst.small->size)
			return (ft_find_ptr(&g_lst.small, p, size));
		g_lst.small = g_lst.small->nxt;
	}
	while (g_lst.large)
	{
		if (p > (void *)g_lst.large && p < (void *)g_lst.large
				+ g_lst.large->size)
			return (ft_find_ptr(&g_lst.large, p, size));
		g_lst.large = g_lst.large->nxt;
	}
	return (malloc(size));
}

/* void    *ft_realloc(void *ptr, size_t size) */
void			*realloc(void *ptr, size_t size)
{
	void		*p;

	if ((int)size < 0)
		return (NULL);
	if (!ptr)
		return (malloc(size));
	else if (!size)
	{
		free(ptr);
		return (malloc(16));
	}
	p = ft_find_zone(ptr, size);
	return (p);
}
