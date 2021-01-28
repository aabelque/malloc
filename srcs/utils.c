/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:37:31 by aabelque          #+#    #+#             */
/*   Updated: 2021/01/28 21:42:49 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "malloc.h" */
#include "../include/malloc.h"

void        *ft_create_zone(t_page *prev, size_t size, size_t len)
{
    t_page    *new;

    if (!(new = (t_page *)mmap(0, size, PROT, FLGS, -1, 0)))
        return (NULL);
    new->rest = size - (STRUCT(t_page) + STRUCT(t_block));
    new->free = 1;
    /* ft_putstr("new: 0x"); */
    /* ft_putstr(ft_lltoa_base((long long)new, 16)); */
    /* ft_putstr("\n"); */
    new->blk = (void *)new + STRUCT(t_page);  
    /* ft_putnbr(STRUCT(t_page)); */
    /* ft_putstr("\n"); */
    new->blk->len = len;
    new->blk->free = 0;
    new->blk->p = (void *)new->blk + STRUCT(t_block);
    /* ft_putnbr(STRUCT(t_block)); */
    /* ft_putstr("\n"); */
    /* ft_putstr("new.blk.p: 0x"); */
    /* ft_putstr(ft_lltoa_base((long long)new->blk->p, 16)); */
    /* ft_putstr("\n"); */
    new->blk->nxt = (void *)new->blk + STRUCT(t_block) + len;
    new->blk->nxt->prv = (void *)new->blk;
    new->blk->prv = (void *)new->blk;
    if (prev)
        prev->nxt = (void *)new;
        /* new->prv = prev; */
    return ((void *)new);
}

size_t      ft_getalign(size_t size, int align)
{
    if (size % align)
        return size + align - (size % align);
    return (size != 0 ? size : align);
}
