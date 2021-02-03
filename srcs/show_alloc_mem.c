/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:09:37 by aabelque          #+#    #+#             */
/*   Updated: 2021/02/03 17:02:17 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
/* #include "../include/malloc.h" */

static void     print_mem(t_page *page, int *i)
{
    ft_putstr(ft_lltoa_base((long long)page, 16));
    write(1, "\n", 1);
    while (page && page->nxt)
    {
        while (page->blk && page->blk->nxt)
        {
            if (!page->blk->free)
            {
                write(1, "0x", 2);
                ft_putstr(ft_lltoa_base((long long)page->blk->p, 16));
                ft_putstr(" - ");
                write(1, "0x", 2);
                ft_putstr(ft_lltoa_base((long long)page->blk->nxt, 16));
                ft_putstr(" : ");
                ft_putnbr(page->blk->len);
                ft_putstr(" octets\n");
                *i += page->blk->len;
            }
            page->blk = page->blk->nxt;
        }
        page = page->nxt;
        write(1, "\n", 1);
    }
}

void            show_alloc_mem(void)
{
    int     i;
    t_page  *tiny;
    t_page  *small;
    t_page  *large;

    i = 0;
    tiny = g_lst.tiny;
    small = g_lst.small;
    large = g_lst.large;
    ft_putstr("TINY : ");
    print_mem(tiny, &i);
    ft_putstr("SMALL : ");
    print_mem(small, &i);
    ft_putstr("LARGE : ");
    print_mem(large, &i);
    ft_putstr("Total : ");
    ft_putnbr(i);
    ft_putstr(" octets\n");
}
