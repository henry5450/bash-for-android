#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
static void t(const char *p, int mode) {
  int r; errno = 0;
  r = faccessat(AT_FDCWD, p, mode, AT_EACCESS);
  printf("  faccessat(AT_EACCESS) %-24s -> %2d %s\n", p, r, r<0?strerror(errno):"OK");
  errno = 0;
  r = faccessat(AT_FDCWD, p, mode, 0);
  printf("  faccessat(flags=0)    %-24s -> %2d %s\n", p, r, r<0?strerror(errno):"OK");
  errno = 0;
  r = access(p, mode);
  printf("  access(2)             %-24s -> %2d %s\n", p, r, r<0?strerror(errno):"OK");
}
int main(void) {
  puts("W_OK on /data/local/tmp (0771 shell:shell, 应当可写):");
  t("/data/local/tmp", W_OK);
  puts("\nW_OK on /tmp (tmpfs 0771 shell:shell, 应当可写):");
  t("/tmp", W_OK);
  return 0;
}
