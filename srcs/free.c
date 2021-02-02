/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:44:25 by aabelque          #+#    #+#             */
/*   Updated: 2021/02/01 22:38:23 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "malloc.h" */
#include "../include/malloc.h"

//TODO refactor free karge function
static int      ft_free_large(t_page **page, void *ptr)
{
    t_page  *zone;

    if (!*page)
        return (-1);
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

static int      ft_find_free(t_page *page, void *ptr)
{
    t_block  *blk;

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
                return (1);
            }
            blk = blk->nxt;
        }
        page = page->nxt;
    }
    return (0);
}

static void     ft_defrag(t_block **curr, t_block **prev, t_block **next)
{
    if ((*prev)->free)
    {
        (*prev)->nxt = (*curr)->nxt;
        (*curr)->prv = (*prev)->prv;
        *curr = *prev;
        (*curr)->len = (long)(*curr)->nxt - (long)*curr;
    }
    else if ((*next)->free)
    {
        (*next)->prv = (*curr)->prv;
        (*curr)->nxt = (*next)->nxt;
        *next = *curr;
        (*next)->len = (long)(*curr)->nxt - (long)*curr;
    }
}

static void     ft_find_fragment(t_page *page)
{
    t_block     *curr;
    t_block     *next;
    t_block     *prev;

    if (!page)
        return ;
    curr = page->blk;
    next = curr->nxt;
    prev = curr->prv;
    while (curr && curr->nxt)
    {
        if (curr->free && (next->free || prev->free))
                ft_defrag(&curr, &prev, &next);
        prev = curr->prv;
        curr = next;
        next = next->nxt;
    }
}

void            ft_free(void *ptr)
{
    if (!ptr)
        return;

    if (ft_find_free(g_lst.tiny, ptr))
    {
        ft_find_fragment(g_lst.tiny);
        return ;
    }
    else if (ft_find_free(g_lst.small, ptr))
    {
        ft_find_fragment(g_lst.small);
        return ;
    }
    else
        ft_free_large(&g_lst.large, ptr);
}
