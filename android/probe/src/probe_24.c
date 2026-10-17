#include <stdlib.h>
#include <unistd.h>

int
main(int c, char **v)
{
	void *x;

	x = sbrk (4096);
	exit ((x == (void *)-1) ? 1 : 0);
}
