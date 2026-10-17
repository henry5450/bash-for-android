#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <wchar.h>
int main(void) {
  char *r;
  printf("MB_CUR_MAX(before) = %d\n", (int)MB_CUR_MAX);
  r = setlocale(LC_ALL, "en_US.UTF-8");
  printf("setlocale(en_US.UTF-8) = %s\n", r ? r : "(NULL)");
  printf("MB_CUR_MAX(after)  = %d\n", (int)MB_CUR_MAX);
  printf("wcwidth(0x0301)    = %d\n", wcwidth(0x0301));
  printf("wcwidth(0x200b)    = %d\n", wcwidth(0x200b));
  printf("wcwidth(0x4e2d)    = %d  (中, expect 2)\n", wcwidth(0x4e2d));
  r = setlocale(LC_ALL, "C.UTF-8");
  printf("setlocale(C.UTF-8) = %s\n", r ? r : "(NULL)");
  printf("MB_CUR_MAX(C.UTF-8)= %d\n", (int)MB_CUR_MAX);
  printf("wcwidth(0x4e2d)    = %d\n", wcwidth(0x4e2d));
  return 0;
}
