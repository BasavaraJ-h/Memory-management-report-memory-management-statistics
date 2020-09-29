#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
void main()
{
	char command[128];
	

  int pid;
  printf("Enter a process id: \n");
  scanf("%d", &pid);
   snprintf( command,sizeof(command), "pmap %d ",pid       );
  system(command);

}
