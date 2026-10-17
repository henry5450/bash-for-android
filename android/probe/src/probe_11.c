#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <sys/types.h>
#include <signal.h>
#include <setjmp.h>
#include <stdlib.h>

int
main()
{
#if !defined (_POSIX_VERSION) || !defined (HAVE_POSIX_SIGNALS)
exit (1);
#else

int code;
sigset_t set, oset, nset;
sigjmp_buf xx;

/* get the mask */
sigemptyset(&set);
sigemptyset(&oset);

sigprocmask(SIG_BLOCK, (sigset_t *)NULL, &oset);
/* paranoia -- make sure SIGINT is not blocked */
sigdelset (&oset, SIGINT);
sigprocmask (SIG_SETMASK, &oset, (sigset_t *)NULL);

/* save it */
code = sigsetjmp(xx, 1);
if (code)
{
  sigprocmask(SIG_BLOCK, (sigset_t *)NULL, &nset);
  /* could compare nset to oset here, but we just look for SIGINT */
  if (sigismember (&nset, SIGINT))
    exit(1);
  exit(0);
}

/* change it so that SIGINT is blocked */
sigaddset(&set, SIGINT);
sigprocmask(SIG_BLOCK, &set, (sigset_t *)NULL);

/* and siglongjmp */
siglongjmp(xx, 10);
exit(1);
#endif
}
