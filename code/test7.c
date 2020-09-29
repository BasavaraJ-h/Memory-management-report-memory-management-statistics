#include <stdio.h>
#include <linux/kernel.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  // Get args from terminal and call petime (get elapsed time) with that PID.
  long int helloCheck = syscall(552, atoi(argv[1]));
  printf("System call sys_petime returned %ld\n", helloCheck);
  return 0;
}

