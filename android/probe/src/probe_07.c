#ifdef HAVE_UNISTD_H
#  include <unistd.h>
#endif
#include <stdlib.h>
char *
getenv (const char *name)
{
return "42";
}
int
main()
{
char *s;
/* The next allows this program to run, but does not allow bash to link
   when it redefines getenv.  I'm not really interested in figuring out
   why not. */
#if defined (NeXT)
exit(1);
#endif
s = getenv("ABCDE");
exit(s == 0);	/* force optimizer to leave getenv in */
}
