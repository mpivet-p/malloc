/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:50:35 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/10/03 14:08:57 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <stdio.h>
#include "libft_malloc.h"

extern t_page *g_heap;

void	clean_pages(void)
{
	t_page *ptr = g_heap;
	t_page *prev_page;
	t_page *next_page;

	while (ptr)
	{
		next_page = ptr->next;
		if (ptr->chunks == ptr->chunks_available)
		{
			if (ptr == g_heap)
			{
				g_heap = ptr->next;
			}
			else
				prev_page->next = ptr->next;
			munmap((void*)ptr, ptr->size);
		}
		else
			prev_page = ptr;
		ptr = next_page;
	}
}

void	ft_free(void *ptr)
{
	t_chunk	*chunk;
	t_page	*page_ptr;

	if ((chunk = get_chunk(ptr, &page_ptr)) != NULL)
	{
		chunk->available = TRUE;
		page_ptr->chunks_available++;
	}
	clean_pages();
}
