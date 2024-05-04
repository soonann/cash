#include <stdio.h>
#include <unistd.h>

void showps1() {
  char buf[256];
  getcwd(buf, sizeof(buf));
  printf("%s$ \n", buf);
}

int main() { showps1(); }
