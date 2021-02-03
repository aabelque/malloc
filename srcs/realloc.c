/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:15:13 by aabelque          #+#    #+#             */
/*   Updated: 2021/02/03 17:06:57 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
/* #include "../include/malloc.h" */

static void     *ft_find_ptr(t_page *zone, void *ptr, size_t len)
{
    void    *new;
    t_block *blk;

    new = NULL;
    blk = zone->blk;
    while (zone && zone->nxt)
    {
        while (blk && blk->nxt)
        {
            if (ptr == blk->p)
            {
                if (len <= blk->len)
                    return (ptr);
                new = malloc(len);
                free(ptr);
                return (new);
            }
            blk = blk->nxt;
        }
        zone = zone->nxt;
    }
    return (new);
}

void    *realloc(void *ptr, size_t size)
{
    void *p;

    if (!ptr)
        return (malloc(size));
    if (!size)
    {
        free(ptr);
        return (malloc(0));
    }
    if ((p = ft_find_ptr(g_lst.tiny, ptr, size)))
        return (p);
    else if ((p = ft_find_ptr(g_lst.small, ptr, size)))
        return (p);
    else
        p = ft_find_ptr(g_lst.large, ptr, size);
    return (p);
}
