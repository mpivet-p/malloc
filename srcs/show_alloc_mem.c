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

extern t_page *g_heap;

static void	print_hex(uint64_t nbr)
{
	char	result[19];
	int		i;
	int		c;

	i = 0;
	bzero(result, 17);
	result[0] = '0'
	result[1] = 'x'
	while (i < 16)
	{
		c = (nbr & ((0xF << (15 - i) * 4))) >> ((15 - i) * 4);
		result[i + 2] = "0123456789ABCDEF"[c];
		i++;
	}
	result[i] = 0;
	i = 0;
	while (result[i] && result[i] == '0')
		i++;
	ft_putstr(ft_strcat(result + 2, result + i + 2));
}

static void	print_memory(t_page *heap)
{
	static char	*pages_sizes[3] = {"TINY", "SMALL", "LARGE"}
	t_block		*block;
	int			sum;

	sum = 0;
	while (heap != NULL)
	{
		ft_putstr(pages_size[heap->type]);
		ft_putstr(": ");
		print_hex(heap);
		block = heap->first_block;
		write(1, "\n", 1);
		while (block)
		{
			if (block->freed == FALSE)
			{
				print_hex(block + sizeof(t_block));
				ft_putstr(" - ");
				print_hex(block + sizeof(t_block) + block->size);
				ft_putstr(" : ");
				ft_putnbr(block->size);
				ft_putstr(" octets\n");
				sum += block->size;
			}
			block = block->next;
		}
	}
	ft_putstr("Total : ");
	ft_putnbr(sum);
	ft_putstr("octets\n");
}

void	show_alloc_mem(void)
{
	print_memory(g_heap);
}
