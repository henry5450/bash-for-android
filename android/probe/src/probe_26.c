#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fnmatch.h>
#include <locale.h>

char *pattern = "[[=a=]]";

/* char *string = "ä"; */
unsigned char string[4] = { '\xc3', '\xa4', '\0' };

int
main (int c, char **v)
{
  setlocale (LC_ALL, "en_US.UTF-8");
  if (fnmatch (pattern, (const char *)string, 0) != FNM_NOMATCH)
    exit (0);
  exit (1);
}
