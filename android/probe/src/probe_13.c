#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
main()
{
	double y = 0.0;
	char abuf[1024];

	sprintf(abuf, "%A", y);
	exit(strchr(abuf, 'P') == (char *)0);
}
