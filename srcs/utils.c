/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:37:31 by aabelque          #+#    #+#             */
/*   Updated: 2021/02/01 20:44:06 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "malloc.h" */
#include "../include/malloc.h"

void        ft_init_block(t_block **blk, size_t len)
{
    t_block *new;

    if (len ) 
        return ;
}

void        *ft_alloc_large(t_page **page, size_t len)
{
    t_page  *new;

    if (!(new = (t_page *)mmap(0, len, PROT, FLGS, -1, 0)))
        return (NULL);
    new->nxt = (void *)new + len;
    new->rest = 0;
    new->free = 0;
    new->blk = (void *)new + STRUCT(t_page);
    new->blk->free = 0;
    new->blk->len = len;
    new->blk->p = (void *)new->blk + STRUCT(t_block);
    new->blk->nxt = (void *)new->blk->p + len;
    new->blk->nxt->prv = (void *)new->blk;
    new->blk->prv = (void *)new->blk;
    if (*page)
    {
        (*page)->nxt = (void *)new;
        return (new->blk->p);
    }
    *page = new;
    return ((*page)->blk->p);
}

void        *ft_create_zone(t_page *prev, size_t size, size_t len)
{
    t_page    *new;

    if (!(new = (t_page *)mmap(0, size, PROT, FLGS, -1, 0)))
        return (NULL);
    new->nxt = (void *)new + size;
    new->nxt->nxt = NULL;
    new->rest = size - (STRUCT(t_page) + STRUCT(t_block));
    new->free = 1;
    new->blk = (void *)new + STRUCT(t_page);  
    new->blk->len = len;
    new->blk->free = 0;
    new->blk->p = (void *)new->blk + STRUCT(t_block);
    new->blk->nxt = (void *)new->blk + STRUCT(t_block) + len;
    new->blk->nxt->free = 1;
    new->blk->prv = (void *)new->blk;
    /* new->blk->nxt->nxt = (void *)new + size; */
    new->blk->nxt->prv = (void *)new->blk;
    /* new->blk->nxt->nxt->nxt = NULL; */
    if (prev)
        prev->nxt = (void *)new;
    return ((void *)new);
}

size_t      ft_getalign(size_t size, int align)
{
    if (size % align)
        return size + align - (size % align);
    return (size != 0 ? size : align);
}
