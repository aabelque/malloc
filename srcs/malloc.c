/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azziz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:27:42 by azziz             #+#    #+#             */
/*   Updated: 2021/01/28 21:42:49 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "malloc.h" */
#include "../include/malloc.h"
#include <stdio.h>

static t_block     *ft_findblock(t_page **page, size_t sz)
{
    t_block     *blk;
    t_block     *new;

    blk = (void *)(*page)->blk;
    new = NULL;
    while (blk && blk->nxt)
    {
        if (blk->free && sz <= blk->len)
            return (blk);
        blk = blk->nxt;
    }
    new = blk;
    new->prv = (void *)blk->prv;
    new->len = sz;
    (*page)->rest -= sz - STRUCT(t_block);
    new->free = ((*page)->rest) ? 1 : 0;
    new->nxt = (void *)new + STRUCT(t_block) + sz;
    new->nxt->prv = (void *)new;
    new->p = (void *)new + STRUCT(t_block);
    /* ft_putstr("blk->prv: 0x"); */
    /* ft_putstr(ft_lltoa_base((long long)blk->prv, 16)); */
    /* ft_putstr("\n"); */
    /* ft_putstr("xxxx\n"); */
    /* blk->nxt->prv = blk; */
    /* /1* ft_putstr("xxxx\n"); *1/ */
    /* ft_putnbr(blk->rest); */
    /* blk = blk->nxt; */
    /* ft_putstr("\n"); */
    /* ft_putstr("0x"); */
    /* ft_putstr(ft_lltoa_base((long long)blk->prv, 16)); */
    /* ft_putstr("\n"); */
    /* ft_putstr(ft_lltoa_base((long long)blk, 16)); */
    /* ft_putstr("\n"); */
    /* ft_putnbr(blk->rest); */
    /* ft_putstr("\n"); */
    /* if (blk->free && sz < blk->rest) */
    /* { */
    /*     blk += sz + STRUCT; */
    /*     blk->nxt += sz + STRUCT; */
    /*     blk->len = sz; */
    /*     blk->free = (blk->rest) ? 1 : 0; */
    /* } */
    return (new);
}

static void     *ft_getblock(t_page **zone, size_t len, size_t len_zone)
{
    t_page      *page;
    t_block     *new;

    if (!*zone)
    {
        *zone = (t_page *)ft_create_zone(*zone, len_zone, len);
        /* ft_putstr("0x"); */
        /* ft_putstr(ft_lltoa_base((long long)(*zone)->prv, 16)); */
        /* write(1, "\n", 1); */
        /* ft_putstr("0x"); */
        /* ft_putstr(ft_lltoa_base((long long)(*zone), 16)); */
        /* write(1, "\n", 1); */
        return ((void *)(*zone)->blk->p);
    }
    new = NULL;
    page = *zone;
    while (page)
    {
        if (len <= page->rest)
            if ((new = ft_findblock(&page, len)))
                return (new->p);
        page = page->nxt;
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
    {
        /* ft_putstr("0x"); */
        /* ft_putstr(ft_lltoa_base((long long)g_lst.tiny + STRUCT, 16)); */
        /* write(1, "\n", 1); */
        return(ft_getblock(&g_lst.tiny, size, TINY_ZONE));
    }
    else if (size <= SMALL)
        return(ft_getblock(&g_lst.small, size, SMALL_ZONE));
    else
    {
        return (NULL);
    }
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
    /* ft_putstr("p: 0x"); */
    /* ft_putstr(ft_lltoa_base((long long)p, 16)); */
    /* write(1, "\n", 1); */
    /* ft_putstr("tiny->nxt: 0x"); */
    /* ft_putstr(ft_lltoa_base((long long)g_lst.tiny->nxt, 16)); */
    /* write(1, "\n", 1); */
    /* ft_putstr("tiny->nxt->nxt: 0x"); */
    /* ft_putstr(ft_lltoa_base((long long)g_lst.tiny->nxt->nxt, 16)); */
    /* write(1, "\n", 1); */
    /* show_alloc_mem(); */
    return (p);
}
