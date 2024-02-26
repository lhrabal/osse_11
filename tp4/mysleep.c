#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Fonction vide pour ne rien faire à la récepion du signal.
void ignore(){}

void mysleep(unsigned int nb)
{
    signal(SIGALRM, ignore);
    alarm(nb);
    pause();
}


int main(int argc, char* argv[])
{
    if (argc!=2) {
        fprintf(stderr, "usage: %s <int>\n", argv[0]);
        return 1;
    }

    printf("%s [%d]\n", argv[0], getpid());
    mysleep(strtoul(argv[1], NULL, 10));
    printf("done.\n");

    return 0;
}
