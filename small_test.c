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

	addr1 = malloc(0);
	printf("%p\n", addr1);
	addr2 = realloc(addr1, 0);
	printf("%p\n", addr2);
	addr3 = realloc(addr2, 150000);
	printf("%p\n", addr3);

	addr1 = ft_malloc(0);
	printf("%p\n", addr1);
	addr2 = ft_realloc(addr1, 0);
	printf("%p\n", addr2);
	addr3 = ft_realloc(addr2, 150000);
	printf("%p\n", addr3);
	//addr2 = (char*)ft_malloc(sizeof(char) * 65);
	//addr1 = (char*)ft_malloc(sizeof(char) * 65);
	//addr1 = (char*)ft_malloc(sizeof(char) * 12);
	//addr1 = (char*)ft_malloc(sizeof(char) * 25000);
	//addr1 = (char*)ft_malloc(sizeof(char) * 12);
	//addr1 = (char*)ft_malloc(sizeof(char) * 65);
	//addr1 = (char*)ft_malloc(sizeof(char) * 65);
	//addr3 = (char*)ft_malloc(sizeof(char) * 24000);
	//show_alloc_mem();
	//ft_free(addr2);
	//ft_free(addr1);
	//printf("\n");
	//show_alloc_mem();
}
