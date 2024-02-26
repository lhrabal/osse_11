#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int child_pid = fork();

    if (child_pid == 0)
    {
        sleep(2);
        printf("\n");
        return 0;
    }

    int re_child_pid = fork();
    if (re_child_pid == 0)
    {
        sleep(1);
        printf(" world");
        return 0;
    }

    printf("hello");

    wait(NULL);
    wait(NULL);

    return 0;
}
