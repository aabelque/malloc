/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:09:37 by aabelque          #+#    #+#             */
/*   Updated: 2021/01/23 10:25:52 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "malloc.h" */
#include "../include/malloc.h"

static void print_mem(t_block *lst)
{
    ft_putstr(ft_lltoa_base((long long)lst, 16));
    write(1, "\n", 1);
    while (lst && lst->nxt)
    {
        write(1, "0x", 2);
        ft_putstr(ft_lltoa_base((long long)lst, 16));
        ft_putstr(" - ");
        write(1, "0x", 2);
        ft_putstr(ft_lltoa_base((long long)lst->nxt, 16));
        ft_putstr(" : ");
        ft_putnbr((lst->nxt) - (lst));
        ft_putstr(" octets\n");
        lst = lst->nxt;
    }
}

void     show_alloc_mem(void)
{
    t_block *tiny;
    t_block *small;
    t_block *large;

    tiny = g_lst.tiny;
    small = g_lst.small;
    large = g_lst.large;
    ft_putstr("TINY : ");
    print_mem(tiny);
    ft_putstr("SMALL : ");
    print_mem(small);
    ft_putstr("LARGE : ");
    print_mem(large);
}
