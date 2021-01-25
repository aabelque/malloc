/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azziz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:27:42 by azziz             #+#    #+#             */
/*   Updated: 2021/01/25 12:58:50 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "malloc.h" */
#include "../include/malloc.h"
#include <stdio.h>

static t_block  *ft_findblock(t_block *blk, size_t size, size_t szone)
{
    t_block *new;

    write(1, "R", 1);
    write(1, "\n", 1);
    while (blk->nxt)
        blk = blk->nxt;
    if (blk->free)
    {
        if (size < blk->stotal)
        {
            new = blk;
            new->nxt = new + size;
            new->prv = blk;
            new->csize = size;
            new->stotal = blk->stotal - size;
            new->free = (new->stotal) ? 1 : 0;
        }
        return (new - (size - STRUCT));
    }
    else
    {
        new = ft_new_block(szone);
    }
    return (new);
}

static t_block  *ft_getblock(t_block **lst, size_t size, size_t szone)
{
    t_block *cur;
    t_block *new;
    
    cur = *lst;
    if (cur)
        new = ft_findblock(cur, size, szone);
    else
    {
        new = ft_new_block(szone);
        new->nxt = new + (size - STRUCT);
        new->prv = NULL;
        new->csize = size;
        new->stotal = szone - size;
    }
    ft_putnbr(new->csize);
    *lst = new;
    ft_putnbr((*lst)->csize);
    return (new);
}

t_block             *ft_alloc(size_t size)
{
    t_block         *block;
    struct rlimit   *rlp;
    void *p;

    getrlimit(RLIMIT_DATA, rlp);
    if (size > rlp->rlim_max || size > rlp->rlim_cur)
        return (NULL);
    ft_putnbr(size);
    size = ft_getalign(size + STRUCT, 16);
    ft_putnbr(size);
    if (size < TINY)
        block = ft_getblock(&g_lst.tiny, size, TINY_ZONE);
    else if (size < SMALL)
        block = ft_getblock(&g_lst.small, size, SMALL_ZONE);
    else
    {
        if (!block)
        {
            block = ft_new_block(size);
            g_lst.large = block;
        }
    }
    write(1, "P", 1);
    write(1, "\n", 1);
    write(1, "0x", 2);
    ft_putstr(ft_lltoa_base((long long)block, 16));
    p = block;
    write(1, "\n", 1);
    write(1, "0x", 2);
    ft_putstr(ft_lltoa_base((long long)p+STRUCT, 16));
    return (p);
}

void            *ft_malloc(size_t size)
{
    static int  init = 0;
    t_block *p;

    ft_putnbr(init);
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
    ft_putstr(ft_lltoa_base((long long)p, 16));
    write(1, "F", 1);
    write(1, "\n", 1);
    /* show_alloc_mem(); */
    return (p);
}
