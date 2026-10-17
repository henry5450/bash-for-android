#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#include <stdlib.h>
#include <sys/resource.h>
int
main()
{
struct rlimit r;
exit(sizeof (r.rlim_cur));
}
