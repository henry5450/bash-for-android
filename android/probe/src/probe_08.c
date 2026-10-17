#include <stdlib.h>
#ifdef HAVE_ULIMIT_H
#include <ulimit.h>
#endif
int
main()
{
long maxfds = ulimit(4, 0L);
exit (maxfds == -1L);
}
