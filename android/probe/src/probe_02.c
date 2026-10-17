#include <sys/types.h>
#include <signal.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <stdlib.h>
#if !HAVE_DECL_SYS_SIGLIST
extern char *sys_siglist[];
#endif
int
main()
{
char *msg = sys_siglist[2];
exit(msg == 0);
}
