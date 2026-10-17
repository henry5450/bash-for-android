#include <signal.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <stdlib.h>

typedef void sigfunc(int);

volatile int nsigint;

#ifdef HAVE_POSIX_SIGNALS
sigfunc *
set_signal_handler(int sig, sigfunc *handler)
{
  struct sigaction act, oact;
  act.sa_handler = handler;
  act.sa_flags = 0;
  sigemptyset (&act.sa_mask);
  sigemptyset (&oact.sa_mask);
  sigaction (sig, &act, &oact);
  return (oact.sa_handler);
}
#else
#define set_signal_handler(s, h) signal(s, h)
#endif

void
sigint(int s)
{
  nsigint++;
}

int
main()
{
	nsigint = 0;
	set_signal_handler(SIGINT, sigint);
	kill((int)getpid(), SIGINT);
	kill((int)getpid(), SIGINT);
	exit(nsigint != 2);
}
