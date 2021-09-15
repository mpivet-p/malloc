#include <stdio.h>
#include <stdlib.h>

#include "libft_malloc.h"

int	main(void)
{
	char *addr1;
	char *addr2;

	addr1 = (char*)ft_malloc(sizeof(char) * 65);
	printf("\n");
	addr1 = (char*)ft_malloc(sizeof(char) * 64);
	printf("\n");
	addr2 = (char*)ft_malloc(sizeof(char) * 4);
	printf("\naddr = %p\n", addr2);
	ft_free(addr2);
//	addr = (char*)ft_malloc(sizeof(char) * 42);
//	printf("addr = %p\n", addr);
}
