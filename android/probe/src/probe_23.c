#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>

int
main(int c, char **v)
{
  pid_t pid, p;
  int s, i, n;

  s = 0;
  pid = fork();
  if (pid == 0)
    exit (42);

  /* wait for the process */
  p = wait(&s);
  if (p != pid)
    exit (255);

  /* crack s */
  for (i = 0; i < (sizeof(s) * 8); i++)
    {
      n = (s >> i) & 0xff;
      if (n == 42)
	exit (i);
    }

  exit (254);
}
