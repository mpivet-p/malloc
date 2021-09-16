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

#include "libft_malloc.h"
#include <stdio.h>

extern t_page *g_heap;

void	ft_free(void *ptr)
{
	t_page *page_ptr = g_heap;
	while (page_ptr)
	{
		printf("%p\n", page_ptr);
		if (ptr > (void*)page_ptr && ptr < (void*)(page_ptr + page_ptr->size))
		{
			printf("FOUND\n");
		}
		page_ptr = page_ptr->next;
	}
}
