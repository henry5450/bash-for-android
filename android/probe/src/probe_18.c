#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <locale.h>
#include <wchar.h>

int
main(int c, char **v)
{
        int     w;

        setlocale(LC_ALL, "en_US.UTF-8");
        w = wcwidth (0x0301);
	if (w != 0)
	  exit (0);
	w = wcwidth (0x200b);
        exit (w == 0);  /* exit 0 if wcwidth broken */
}
