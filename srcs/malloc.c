/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azziz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:27:42 by azziz             #+#    #+#             */
/*   Updated: 2021/01/29 17:43:11 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "malloc.h" */
#include "../include/malloc.h"

static t_block     *ft_findblock(t_page **page, size_t sz)
{
    t_block     *blk;
    t_block     *new;

    blk = (void *)(*page)->blk;
    while (blk && blk->nxt)
    {
        if (blk->free && sz <= blk->len)
        {
            blk->free = 0;
            (*page)->rest -= blk->len - STRUCT(t_block);
            return (blk);
        }
        blk = blk->nxt;
    }
    new = blk;
    new->prv = (void *)blk->prv;
    new->len = sz;
    new->free = 0;
    (*page)->rest -= sz - STRUCT(t_block);
    new->nxt = (void *)new + STRUCT(t_block) + sz;
    new->nxt->prv = (void *)new;
    new->p = (void *)new + STRUCT(t_block);
    if (!(*page)->rest)
        (*page)->free = 0;
    return (new);
}

static void     *ft_getblock(t_page **zone, size_t len, size_t len_zone)
{
    t_page      *page;
    t_block     *new;

    if (!*zone)
    {
        *zone = (t_page *)ft_create_zone(*zone, len_zone, len);
        return ((void *)(*zone)->blk->p);
    }
    page = *zone;
    if (page->free)
    {
        while (page)
        {
            if ((len + STRUCT(t_block)) <= page->rest)
                if ((new = ft_findblock(&page, len)))
                    return (new->p);
            page = page->nxt;
        }
    }
    page = ft_create_zone(*zone, len_zone, len);
    return (page->blk->p);
}

static void     *ft_alloc(size_t size)
{
    void            *new;
    struct rlimit   rlp;

    size = ft_getalign(size, 16);
    getrlimit(RLIMIT_DATA, &rlp);
    if (size > rlp.rlim_max || size > rlp.rlim_cur)
        return (NULL);
    if (size <= TINY)
        return(ft_getblock(&g_lst.tiny, size, TINY_ZONE));
    else if (size <= SMALL)
        return(ft_getblock(&g_lst.small, size, SMALL_ZONE));
    else
        return (ft_alloc_large(&g_lst.large, size));
    return (NULL);
}

void            *ft_malloc(size_t size)
{
    static int  init = 0;
    void        *p;

    p = NULL;
    if ((int)size <= 0)
        return (NULL);
    if (!init)
    {
        g_lst.tiny = NULL;
        g_lst.small = NULL;
        g_lst.large = NULL;
        init++;
    }
    p = ft_alloc(size);
    return (p);
}
