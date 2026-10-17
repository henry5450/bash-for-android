#include <stdio.h>
typedef int (*_bashfunc)(const char *, ...);
#include <stdlib.h>
int
main()
{
_bashfunc pf;
pf = (_bashfunc) printf;
exit(pf == 0);
}
