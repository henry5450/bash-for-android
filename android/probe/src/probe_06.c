#include <sys/types.h>
#include <stdlib.h>
#if HAVE_INTTYPES_H
#include <inttypes.h>
#endif
#if HAVE_STDINT_H
#include <stdint.h>
#endif

int
main()
{
#if HAVE_QUAD_T
quad_t x;
exit(sizeof (x));
#else
exit (0);
#endif
}
