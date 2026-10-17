#include <sys/types.h>
#include <sys/stat.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <stdio.h>
#include <stdlib.h>

/* Add more tests in here as appropriate. */
int
main()
{
int fd, err;

#if defined (HAVE_MKFIFO)
exit (0);
#endif

#if !defined (S_IFIFO) && (defined (_POSIX_VERSION) && !defined (S_ISFIFO))
exit (1);
#endif

#if defined (NeXT)
exit (1);
#endif
err = mkdir("bash-aclocal", 0700);
if (err < 0) {
  perror ("mkdir");
  exit(1);
}
fd = mknod ("bash-aclocal/sh-np-autoconf", 0666 | S_IFIFO, 0);
if (fd == -1) {
  rmdir ("bash-aclocal");
  exit (1);
}
close(fd);
unlink ("bash-aclocal/sh-np-autoconf");
rmdir ("bash-aclocal");
exit(0);
}
