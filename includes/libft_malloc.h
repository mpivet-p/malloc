/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_malloc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 16:20:58 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/10/03 14:41:51 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <stddef.h>
# include <stdint.h>

# define PAGE_SIZE			4096
# define TINY_HEAP_SIZE		16384
# define TINY_HEAP			0
# define TINY_BLOCK_SIZE	128
# define SMALL_HEAP_SIZE	65536
# define SMALL_BLOCK_SIZE	512
# define SMALL_HEAP			1
# define LARGE_HEAP			2

# define TRUE	1
# define FALSE	0

void	*malloc(size_t size);
/*void	free(void *ptr);
void	*realloc(void *ptr, size_t size);
*/

typedef struct	s_page
{
	struct s_page	*next;
	struct s_block	*first_block;
	size_t			size;
	size_t			blocks;
	uint8_t			block_available;
	uint8_t			type;
	char			c[2];
}				t_page;

typedef struct	s_block
{
	struct s_block	*next;
	uint16_t		size;
	uint8_t			freed;
	char			c;
}				t_block;

#endif
