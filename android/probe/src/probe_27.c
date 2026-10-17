#include <string.h>
int main(void) {
  const char *buf = "abc";
  return strchrnul (buf, 'd') != buf + 3;
}
