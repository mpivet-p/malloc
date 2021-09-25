#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	char *addr1;
	char *addr2;
	char *addr3;

/*	for (size_t i = 0; i < 2000000; i++)
	{
		if (i % 2 == 0)
		{
			addr1 = malloc(8);
			addr2 = malloc(80);
			addr3 = malloc(800);
		}
		else
		{
			addr1 = realloc(addr1, i % 80);
			addr2 = realloc(addr2, i % 800);
			addr3 = realloc(addr3, i);
		}
		if (i % 10000 == 0)
			printf("%p %p %p %zu\n", addr1, addr2, addr3, i);
		if (addr1 == NULL || addr2 == NULL || addr3 == NULL)
		{
			printf("%p %p %p %zu\n", addr1, addr2, addr3, i);
		}
	}*/
	for (int i = 0; i < 15000; i++)
	{
		addr1 = malloc(8);
		memset(addr1, 42, 8);
	}
	//addr2 = malloc(80);
	//addr3 = malloc(800);
	//free(addr1);
	//free(addr2);
	//free(addr3);
}
