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
#include <stdio.h>

extern t_page *g_heap;

void	*realloc(void *ptr, size_t size)
{
	static	size_t sizes[3] = {TINY_CHUNK_SIZE, SMALL_CHUNK_SIZE, 0};
	t_chunk	*chunk;
	t_page	*page_ptr;

	write(1, "New realloc\n", 13);
	if (ptr != NULL && (chunk = get_chunk(ptr, &page_ptr)) != NULL && size > 0)
	{
		if (size <= sizes[page_ptr->type])
		{
			chunk->size = size;
			return (ptr);
		}
		else 
		{
			free(ptr);
			return (malloc(size));
		}
	}
	else if (ptr == NULL)
		return (malloc(size));
	write(1, "X", 1);
	return (NULL);
}
