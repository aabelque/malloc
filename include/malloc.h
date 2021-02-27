/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azziz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:20:29 by azziz             #+#    #+#             */
/*   Updated: 2021/02/27 15:03:06 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <sys/resource.h>

# define PROT (PROT_READ | PROT_WRITE)
# define FLGS (MAP_ANON | MAP_PRIVATE)
# define PS getpagesize()
# define SMALL 4096
# define TINY 512
# define HEADER ft_getalign(sizeof(t_heap), 16)
# define TINY_ZONE (TINY * 100)
# define SMALL_ZONE (SMALL * 100)
# define HEAP_SHIFT(start) ((void *)start + HEADER)
/* # define BLK_SHIFT(start) ((void *)start + STRUCT(t_block)) */

typedef struct	s_block
{
	short			free;
	size_t			len;
	struct s_block	*nxt;
	struct s_block	*prv;
}				t_block;

typedef struct	s_heap
{
	short			free;
	/* size_t			free_size; */
	size_t			size;
	size_t			nb_heap;
	/* t_block			*blk; */
	struct s_heap	*nxt;
	struct s_heap	*prv;
}				t_heap;

typedef struct	s_malloc
{
	t_heap			*tiny;
	t_heap			*small;
	t_heap			*large;
}				t_malloc;

t_malloc			g_lst;

t_heap			**find_heap(void *ptr, t_heap **current);
int				release_heap(t_heap *heap);
void			*reallocf(void *ptr, size_t size);
void			*calloc(size_t count, size_t size);
void			free(void *ptr);
void			*malloc(size_t size);
size_t			ft_getalign(size_t size, int align);
t_block			*ft_new_block(size_t size);
void			show_alloc_mem(void);
void			*increase_heap(t_heap *last, size_t size, size_t len);
void			*increase_large_heap(t_heap **heap, size_t len, int sz_struct);
t_block			*ft_init_block(t_block *nw, t_block *blk, size_t len);
void			free_heap(t_heap **heap, t_heap *del);
void			*realloc(void *ptr, size_t size);
void			create_block(t_heap *blk, size_t sz);
void			ft_putchar(char c);
void			ft_putnbr(int n);
size_t			ft_strlen(const char *s);
void			ft_putstr(char const *s);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			ft_hexdump(long n);

#endif
