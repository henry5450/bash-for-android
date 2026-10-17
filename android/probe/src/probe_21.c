#include <stdio.h>
#include <stdlib.h>

int
main()
{
  int n;
  n = snprintf (0, 0, "%s", "0123456");
  exit(n != 7);
}
