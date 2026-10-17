#include <sys/types.h>
#include <signal.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <stdlib.h>
#ifndef UNDER_SYS_SIGLIST_DECLARED
extern char *_sys_siglist[];
#endif
int
main()
{
char *msg = (char *)_sys_siglist[2];
exit(msg == 0);
}
