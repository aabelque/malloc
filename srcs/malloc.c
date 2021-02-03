/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azziz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:27:42 by azziz             #+#    #+#             */
/*   Updated: 2021/02/03 17:23:00 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
/* #include "../include/malloc.h" */

static void         ft_newblock(t_block **new, t_block *blk, size_t sz)
{
    *new = blk;
    (*new)->prv = (void *)blk->prv;
    (*new)->len = sz;
    (*new)->free = 0;
    (*new)->p = (void *)(*new) + STRUCT(t_block);
    (*new)->nxt = (void *)(*new) + STRUCT(t_block) + sz;
    (*new)->nxt->free = 1;
    (*new)->nxt->nxt = blk->nxt;
    (*new)->nxt->prv = (void *)(*new);
    (*new)->nxt->nxt->nxt = NULL;
}

t_block      *ft_findblock(t_page **page, size_t sz)
{
    t_block     *blk;
    t_block     *new;

    blk = (void *)(*page)->blk;
    while (blk && blk->nxt)
    {
        if (blk->free && (sz + STRUCT(t_block)) <= blk->len)
        {
            ft_init_block(&new, &blk, sz + STRUCT(t_block));
            blk->len = sz;
            (*page)->rest -= blk->len - STRUCT(t_block);
            if (!blk->nxt->len)
                blk->nxt->free = 1;
            return (blk);
        }
        blk = blk->nxt;
    }
    ft_newblock(&new, blk, sz);
    (*page)->rest -= sz - STRUCT(t_block);
    if (!(*page)->rest)
        (*page)->free = 0;
    return (new);
}

static void         *ft_getblock(t_page **zone, size_t len, size_t len_zone)
{
    t_page      *page;
    t_block     *new;

    if (!*zone)
    {
        *zone = (t_page *)ft_create_zone(*zone, len_zone, len);
        return ((void *)(*zone)->blk->p);
    }
    page = *zone;
    while (page)
    {
        if (page->free)
        {
            if ((len + STRUCT(t_block)) <= page->rest)
                if ((new = ft_findblock(&page, len)))
                    return (new->p);
        }
        page = page->nxt;
    }
    page = ft_create_zone(*zone, len_zone, len);
    return (page->blk->p);
}

static void         *ft_alloc(size_t size)
{
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

void                *malloc(size_t size)
{
    static int  init = 0;
    void        *p;

    p = NULL;
    write(1, "X\n", 2);
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
