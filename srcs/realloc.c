/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:15:13 by aabelque          #+#    #+#             */
/*   Updated: 2021/02/04 18:17:50 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
/* #include "../include/malloc.h" */

static int      ft_find_zone(void *p)
{
    t_page  *tiny;
    t_page  *small;

    tiny = g_lst.tiny;
    small = g_lst.small;

    while (tiny && tiny->nxt)
    {
        if (p > (void *)tiny && p < (void *)tiny->nxt)
            return (T);
        tiny = tiny->nxt;
    }
    while (small && small->nxt)
    {
        if (p > (void *)small && p < (void *)small->nxt)
            return (S);
        small = small->nxt;
    }
    return (0);
}

static void     *ft_find_ptr(t_page **zone, void *ptr, size_t len)
{
    void    *new;
    t_block *blk;

    new = NULL;
    if (!(*zone))
        return (NULL);
    blk = (*zone)->blk;
    while (*zone && (*zone)->nxt)
    {
        while (blk && blk->nxt)
        {
            if (ptr == blk->p)
            {
                if (len <= blk->len)
                    return (ptr);
                new = malloc(len);
                ft_memcpy(new, ptr, len);
                free(ptr);
                return (new);
            }
            blk = blk->nxt;
        }
        *zone = (*zone)->nxt;
    }
    return (new);
}

/* void    *ft_realloc(void *ptr, size_t size) */
void    *realloc(void *ptr, size_t size)
{
    write(1, "R\n", 2);
    void *p;
    int zone;

    if (!ptr)
        return (malloc(size));
    else if (!size)
    {
        free(ptr);
        return (malloc(16));
    }
    zone = ft_find_zone(ptr);
    if (zone == T)
    {
        if ((p = ft_find_ptr(&g_lst.tiny, ptr, size)))
        return (p);
    }
    else if (zone == S)
    {
        if ((p = ft_find_ptr(&g_lst.small, ptr, size)))
        return (p);
    }
    else
        p = ft_find_ptr(&g_lst.large, ptr, size);
    return (p);
}
