/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:09:37 by aabelque          #+#    #+#             */
/*   Updated: 2021/02/09 17:48:44 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

void		show_heap_list()
{
    int i = 0;
    t_page *tiny = g_lst.tiny;
    t_page *small = g_lst.small;
    t_page *large = g_lst.large;

    printf("DEBUG: g_lst list\n");

    while (tiny) {
        printf(
            "%d. tiny %p, next: %p (size: %zu, rest: %zu, free_space: %d)\n",
            i,
            tiny,
            tiny->nxt,
            tiny->size,
            tiny->rest,
            tiny->free);
        tiny = tiny->nxt;
        i++;
    }

    while (small) {
        printf(
            "%d. small %p, next: %p (size: %zu, rest: %zu, free_space: %d)\n",
            i,
            small,
            small->nxt,
            small->size,
            small->rest,
            small->free);
        small = small->nxt;
        i++;
    }
    while (large) {
        printf(
            "%d. large %p, next: %p (size: %zu, rest: %zu, free_space: %d)\n",
            i,
            large,
            large->nxt,
            large->size,
            large->rest,
            large->free);
        large = large->nxt;
        i++;
    }
}

static inline void		ft_hexdump(long n)
{
	if (n > 15)
		ft_hexdump(n / 16);
	if (n % 16 < 10)
		ft_putchar((n % 16) + 48);
	else
		ft_putchar((n % 16) - 10 + 97);
}

static inline void		print_mem_large(t_page *page, int *i)
{
	ft_hexdump((long)page);
	write(1, "\n", 1);
	while (page)
	{
		write(1, "0X", 2);
		ft_hexdump((long)page->blk->p);
		ft_putstr(" - ");
		write(1, "0X", 2);
		ft_hexdump((long)page->blk->p + page->blk->len);
		ft_putstr(" : ");
		ft_putnbr(page->blk->len);
		ft_putstr(" octets\n");
		*i += page->blk->len;
		page = page->nxt;
	}
}

static inline void		print_mem(t_page *page, int *i)
{
	t_block	*first;
	ft_hexdump((long)page);
	write(1, "\n", 1);
	while (page)
	{
		first = page->blk;
		while (page->blk)
		{
			if (!page->blk->free)
			{
				write(1, "0X", 2);
				ft_hexdump((long)page->blk->p);
				ft_putstr(" - ");
				write(1, "0X", 2);
				ft_hexdump((long)page->blk->p + page->blk->len);
				ft_putstr(" : ");
				ft_putnbr(page->blk->len);
				ft_putstr(" octets\n");
				*i += page->blk->len;
			}
			page->blk = page->blk->nxt;
		}
		page->blk = first;
		page = page->nxt;
		write(1, "\n", 1);
	}
}

void					show_alloc_mem(void)
{
	int		i;
	t_page	*tiny;
	t_page	*small;
	t_page	*large;

	i = 0;
	tiny = g_lst.tiny;
	small = g_lst.small;
	large = g_lst.large;
	ft_putstr("TINY : ");
	print_mem(g_lst.tiny, &i);
	write(1, "\n", 1);
	ft_putstr("SMALL : ");
	print_mem(g_lst.small, &i);
	write(1, "\n", 1);
	ft_putstr("LARGE : ");
	print_mem_large(g_lst.large, &i);
	write(1, "\n", 1);
	ft_putstr("Total : ");
	ft_putnbr(i);
	ft_putstr(" octets\n");
}
