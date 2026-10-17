#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

#ifndef NSIG
#  define NSIG 64
#endif

int
main ()
{
  int n_sigs = 2 * NSIG;
#ifdef SIGRTMIN
  int rtmin = SIGRTMIN;
#else
  int rtmin = 0;
#endif

  exit(rtmin < n_sigs);
}
