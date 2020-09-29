#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char *s;

    s = strdup("UCMO");
    if (s == NULL)
    {
        printf("Can't allocate mem with malloc\n");
        return (EXIT_FAILURE);
    }
    printf("%p\n", (void *)s);
    return 0;
}
