/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_malloc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 16:20:58 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/10/03 16:42:08 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <stddef.h>
# include <stdint.h>
# include <unistd.h>

# define TINY_HEAP_SIZE		((sizeof(t_page) + (100 * (sizeof(t_chunk) + TINY_CHUNK_SIZE))) / getpagesize() + 1) * getpagesize()
# define SMALL_HEAP_SIZE	((sizeof(t_page) + (100 * (sizeof(t_chunk) + SMALL_CHUNK_SIZE))) / getpagesize() + 1) * getpagesize()


# define MAP_ANONYMOUS		0x20

# define TINY_CHUNK_SIZE	64
# define SMALL_CHUNK_SIZE	512

# define TINY_PAGE			0
# define SMALL_PAGE			1
# define LARGE_PAGE			2

# define TRUE	1
# define FALSE	0

void	*ft_malloc(size_t size);
void	ft_free(void *ptr);
/*void	*realloc(void *ptr, size_t size);
*/
size_t	get_mempage_size(size_t size);
int		get_page_type(size_t size);

typedef struct	s_page
{
	struct s_page	*next;
	struct s_chunk	*first_chunk;
	size_t			size;
	size_t			chunks;
	uint8_t			chunks_available;
	uint8_t			type;
	uint16_t		canary;
	char			c[8];
}				t_page;

typedef struct	s_chunk
{
	struct s_chunk	*next;
	void			*data;
	uint8_t			available;
	uint16_t		canary;
	char			c;
}				t_chunk;

#endif
