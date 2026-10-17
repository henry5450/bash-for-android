#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif /* HAVE_UNISTD_H */
#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif
#if defined(HAVE_DIRENT_H)
# include <dirent.h>
#else
# define dirent direct
# ifdef HAVE_SYS_NDIR_H
#  include <sys/ndir.h>
# endif /* SYSNDIR */
# ifdef HAVE_SYS_DIR_H
#  include <sys/dir.h>
# endif /* SYSDIR */
# ifdef HAVE_NDIR_H
#  include <ndir.h>
# endif
#endif /* HAVE_DIRENT_H */
#include <stdlib.h>
int
main()
{
DIR *dir;
int fd, err;
err = mkdir("bash-aclocal", 0700);
if (err < 0) {
  perror("mkdir");
  exit(1);
}
unlink("bash-aclocal/not_a_directory");
fd = open("bash-aclocal/not_a_directory", O_WRONLY|O_CREAT|O_EXCL, 0666);
write(fd, "\n", 1);
close(fd);
dir = opendir("bash-aclocal/not_a_directory");
unlink("bash-aclocal/not_a_directory");
rmdir("bash-aclocal");
exit (dir == 0);
}
