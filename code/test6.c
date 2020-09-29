#include <linux/unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>

#define systemmemaccess 551

int main(int argc, char *argv[])
{
        int pid;
        printf("give a process id: \n");
        scanf("%d", &pid);
    printf("%s",   syscall(systemmemaccess, pid));
        return 0;
}
