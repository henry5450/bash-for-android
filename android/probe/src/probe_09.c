#include <stdio.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <stdlib.h>

int
main()
{
	char	*xpwd;
	xpwd = getcwd(0, 0);
	exit (xpwd == 0);
}
