#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int n = argc;
    int pid[n];
    for (int i = 1; i <= n; i++)
    {
        pid[i] = fork();
        if (pid[i] == 0)
        {
            int ni = strtol(argv[i], NULL, 10);
            sleep(ni);
            printf("%d\n", ni);
            break;
        }
    }

    for (int i = 0; i < n; i++)
        wait(NULL);
    
    return 0;
}
