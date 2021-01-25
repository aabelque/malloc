/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azziz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:20:29 by azziz             #+#    #+#             */
/*   Updated: 2021/01/25 17:24:56 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define PROT (PROT_READ | PROT_WRITE)
# define FLGS (MAP_ANON | MAP_PRIVATE)
# define SMALL getpagesize()
# define TINY SMALL / 4
# define STRUCT ft_getalign(sizeof(t_block), 16)
# define TINY_ZONE (TINY * 100)
# define SMALL_ZONE (SMALL * 100)

# include "../libft/include/libft.h"
# include <sys/mman.h>
# include <unistd.h>
# include <sys/resource.h>


typedef struct  s_block
{
    short           free;
    short           pad[3];
    size_t          csize;
    size_t          stotal;
    struct s_block  *nxt;
    struct s_block  *prv;
}               t_block;

typedef struct  s_malloc
{
    t_block     *tiny;
    t_block     *small;
    t_block     *large;
}               t_malloc;

t_malloc g_lst;

void        *ft_malloc(size_t size);
size_t      ft_getalign(size_t size, int align);
t_block     *ft_new_block(size_t size);
void        show_alloc_mem(void);
void        *ft_alloc(size_t size);
/* void    *realloc(void *ptr, size_t size); */
/* void    free(void *ptr); */

#endif
