#include <linux/unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>

#define systemmemstsaus 549

int main(int argc, char *argv[])
{
        int pid;
        printf(" give process id: \n");
        scanf("%d", &pid);
    printf("%s",   syscall(systemmemstsaus, pid));
        return 0;
}
