#include <stdio.h>
#include <string.h>

void func2() {
  long c = -3;
  (void)c;
}

void func1() {
  long b = -2;
  (void)b;

  func2();
}

int main(void) {
  long a = -1;
  (void)a;

  func1();
}
