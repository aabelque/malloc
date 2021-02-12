/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:09:37 by aabelque          #+#    #+#             */
/*   Updated: 2021/02/12 17:25:43 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

inline void		ft_hexdump(long n)
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
	t_page	*head;

	ft_hexdump((long)page);
	write(1, "\n", 1);
	head = page;
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
	page = head;
}

static inline void		print_mem(t_block *blk)
{
	write(1, "0X", 2);
	ft_hexdump((long)blk->p);
	ft_putstr(" - ");
	write(1, "0X", 2);
	ft_hexdump((long)blk->p + blk->len);
	ft_putstr(" : ");
	ft_putnbr(blk->len);
	ft_putstr(" octets\n");
}

static inline void		search_mem(t_page *page, int *i)
{
	t_block	*first;
	t_page	*head;

	/* ft_hexdump((long)page); */
	/* write(1, "\n", 1); */
	head = page;
	while (page)
	{
		ft_hexdump((long)page);
		write(1, "\n", 1);
		first = page->blk;
		while (page->blk)
		{
			if (!page->blk->free)
			{
				print_mem(page->blk);
				*i += page->blk->len;
			}
			page->blk = page->blk->nxt;
		}
		page->blk = first;
		page = page->nxt;
		write(1, "\n", 1);
	}
	page = head;
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
	search_mem(tiny, &i);
	write(1, "\n", 1);
	ft_putstr("SMALL : ");
	search_mem(small, &i);
	write(1, "\n", 1);
	ft_putstr("LARGE : ");
	print_mem_large(large, &i);
	write(1, "\n", 1);
	ft_putstr("Total : ");
	ft_putnbr(i);
	ft_putstr(" octets\n");
}
