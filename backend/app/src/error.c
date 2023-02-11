#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void err_exit(const char *s) {
  fprintf(stderr, "Error : %s\n", s);
  fprintf(stderr, "\n");
  exit(1);
}
