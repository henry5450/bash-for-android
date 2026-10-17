#include <fnmatch.h>

int
main()
{
#ifdef FNM_EXTMATCH
  return (0);
#else
  return (1);
#endif
}
