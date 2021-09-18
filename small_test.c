#include <stdio.h>
#include <stdlib.h>

#include "libft_malloc.h"

void	get_number_of_pages(size_t size)
{
	size_t	chunks_size = (size <= TINY_CHUNK_SIZE) ? TINY_CHUNK_SIZE : SMALL_CHUNK_SIZE;
	size_t	page_size = 4100;

	int min = sizeof(t_page) + (100 * (sizeof(t_chunk) + chunks_size));
	int n = min / page_size + 1;
	int max = ((n * page_size) - sizeof(t_page)) / (sizeof(t_chunk) + chunks_size);
	printf("%d %d %d %d\n", min, max, n, max & 0xFFFFFFFE);
}

int	main(void)
{
	char *addr1;
	char *addr2;
	char *addr3;

	addr2 = (char*)ft_malloc(sizeof(char) * 65);
	addr1 = (char*)ft_malloc(sizeof(char) * 65);
	addr3 = (char*)ft_malloc(sizeof(char) * 24000);
	show_alloc_mem();
	ft_free(addr2);
	ft_free(addr1);
	printf("\n");
	show_alloc_mem();
}
