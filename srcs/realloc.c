/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:54:06 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/09/12 16:09:07 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

extern t_page *g_heap;

void	*ft_realloc(void *ptr, size_t size)
{
	static	size_t sizes[3] = {TINY_CHUNK_SIZE, SMALL_CHUNK_SIZE, 0};
	t_chunk	*chunk;
	t_page	*page_ptr;

	if ((chunk = get_chunk(ptr, &page_ptr)) != NULL)
	{
		if (size > sizes[page_ptr->type])
		{
			chunk->size = size;
			//allocate more space
		}
		else 
		{
			ft_free(ptr);
			return (ft_malloc(size));
			//free + new malloc
		}
	}
	return (NULL);
}
