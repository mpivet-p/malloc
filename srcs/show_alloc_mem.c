/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 16:11:36 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/09/20 15:21:21 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"
#include <stdio.h>

extern t_page *g_heap;

static void	print_memory(t_page *heap)
{
	static char	*pages_sizes[3] = {"TINY", "SMALL", "LARGE"};
	t_chunk		*chunk;
	size_t		sum = 0;

	while (heap != NULL)
	{
		printf("%s : %p\n", pages_sizes[heap->type], heap);
		chunk = heap->first_chunk;
		while (chunk)
		{
			if (chunk->available == FALSE)
			{
				printf("%p - %p : %zu bytes\n", chunk->data, chunk->data + chunk->size, chunk->size);
				sum += chunk->size;
			}
			chunk = chunk->next;
		}
		heap = heap->next;
	}
	printf("Total : %zu bytes\n", sum);
}

void	show_alloc_mem(void)
{
	print_memory(g_heap);
}
