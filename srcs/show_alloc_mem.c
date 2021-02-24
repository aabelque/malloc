/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:09:37 by aabelque          #+#    #+#             */
/*   Updated: 2021/02/24 12:11:52 by aabelque         ###   ########.fr       */
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

static inline void		print_mem_large(t_heap *heap, int *i)
{
	t_heap	*head;

	ft_hexdump((long)heap);
	write(1, "\n", 1);
	head = heap;
	while (heap)
	{
		write(1, "0X", 2);
		ft_hexdump((long)heap->blk->p);
		ft_putstr(" - ");
		write(1, "0X", 2);
		ft_hexdump((long)heap->blk->p + heap->blk->len);
		ft_putstr(" : ");
		ft_putnbr(heap->blk->len);
		ft_putstr(" octets\n");
		*i += heap->blk->len;
		heap = heap->nxt;
	}
	heap = head;
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

static inline void		search_mem(t_heap *heap, int *i)
{
	t_block	*first;
	t_heap	*head;

	ft_hexdump((long)heap);
	write(1, "\n", 1);
	head = heap;
	while (heap)
	{
		first = heap->blk;
		while (heap->blk)
		{
			if (!heap->blk->free)
			{
				print_mem(heap->blk);
				*i += heap->blk->len;
			}
			heap->blk = heap->blk->nxt;
		}
		heap->blk = first;
		heap = heap->nxt;
		write(1, "\n", 1);
	}
	heap = head;
}

void					show_alloc_mem(void)
{
	int		i;
	t_heap	*tiny;
	t_heap	*small;
	t_heap	*large;

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
