#include <stdio.h>
#include <stdlib.h>

#include "libft_malloc.h"

int	main(void)
{
	char *addr1;
	char *addr2;

	addr1 = (char*)ft_malloc(sizeof(char) * 65);
	dprintf(2, "\naddr = %p\n", addr1);
	ft_free(addr1);

	addr1 = (char*)ft_malloc(sizeof(char) * 64);
	dprintf(2, "\naddr = %p\n", addr1);
	ft_free(addr1);

	addr2 = (char*)ft_malloc(sizeof(char) * 4);
	dprintf(2, "\naddr = %p\n", addr2);
	ft_free(addr2);

	addr1 = (char*)ft_malloc(sizeof(char) * 24000);
	dprintf(2, "\naddr = %p\n", addr1);
	ft_free(addr1);

}
