#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static int
foo(const char *fmt, ...)
{
  va_list args;
  int n;

  va_start(args, fmt);
  n = vsnprintf(0, 0, fmt, args);
  va_end (args);
  return n;
}

int
main()
{
  int n;
  n = foo("%s", "0123456");
  exit(n != 7);
}
