#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif /* HAVE_UNISTD_H */
int
main()
{
  int fd1, fd2, fl;
  fd1 = open("/dev/null", 2);
  if (fcntl(fd1, 2, 1) < 0)
    exit(1);
  fd2 = dup2(fd1, 1);
  if (fd2 < 0)
    exit(2);
  fl = fcntl(fd2, 1, 0);
  /* fl will be 1 if dup2 did not reset the close-on-exec flag. */
  exit(fl != 1);
}
