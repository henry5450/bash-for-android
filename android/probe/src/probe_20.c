#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#ifndef errno
extern int errno;
#endif
int
main()
{
	int	x;

	x = waitpid(-1, (int *)0, WNOHANG|WCONTINUED);
	if (x == -1 && errno == EINVAL)
		exit (1);
	else
		exit (0);
}
