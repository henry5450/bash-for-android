#include <stdio.h>
#if defined (HAVE_LOCALE_H)
#include <locale.h>
#endif
#include <string.h>
#include <stdlib.h>

int
main(int c, char **v)
{
        int     r1, r2;
        char    *deflocale, *defcoll;

#ifdef HAVE_SETLOCALE
        deflocale = setlocale(LC_ALL, "");
	defcoll = setlocale(LC_COLLATE, "");
#endif

#ifdef HAVE_STRCOLL
	/* These two values are taken from tests/glob-test. */
        r1 = strcoll("abd", "aXd");
#else
	r1 = 0;
#endif
        r2 = strcmp("abd", "aXd");

	/* These two should both be greater than 0.  It is permissible for
	   a system to return different values, as long as the sign is the
	   same. */

        /* Exit with 1 (failure) if these two values are both > 0, since
	   this tests whether strcoll(3) is broken with respect to strcmp(3)
	   in the default locale. */
	exit (r1 > 0 && r2 > 0);
}
