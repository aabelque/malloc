/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:44:25 by aabelque          #+#    #+#             */
/*   Updated: 2021/01/30 12:02:38 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "malloc.h" */
#include "../include/malloc.h"

static int  ft_free_large(t_page **page, void *ptr)
{
    t_page  *zone;

    zone = *page;
    while (zone && zone->nxt)
    {
        if (zone->blk->p == ptr)
            if (!(munmap(zone, zone->blk->len)))
            {
                *page = NULL;
                return (0);
            }
        zone = zone->nxt;
    }
    return (-1);
}

static void defrag(t_page *page)
{
}

static int  ft_find_free(t_page *page, void *ptr)
{
    t_block  *blk;

    blk = page->blk;
    while (page)
    {
        while (blk)
        {
            if (ptr == blk->p)
            {
                blk->free = 1;
                page->rest += blk->len + STRUCT(t_block);
                return (1);
            }
            blk = blk->nxt;
        }
        page = page->nxt;
    }
    return (0);
}

void    ft_free(void *ptr)
{
    if (!ptr)
        return;

    if (ft_find_free(g_lst.tiny, ptr))
    {
        defrag(g_lst.tiny);
        return ;
    }
    else if (ft_find_free(g_lst.small, ptr))
    {
        defrag(g_lst.small);
        return ;
    }
    else
        ft_free_large(&g_lst.large, ptr);
}
