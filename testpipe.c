#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int i;
    char *p;

    i = fork();
    if ( i == 0)
        printf("Hello world!\n");
    else
        printf("Hello world999999!\n");
    return 0;
}