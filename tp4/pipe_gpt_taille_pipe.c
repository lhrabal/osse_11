#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int pipe_fd[2];
    int pipe_size;

    if (pipe(pipe_fd) == -1)
    {
        perror("Erreur lors de la création du pipe");
        exit(EXIT_FAILURE);
    }

    pipe_size = fcntl(pipe_fd[0], F_GETPIPE_SZ);

    if (pipe_size == -1)
    {
        perror("Erreur lors de la récupération de la taille du pipe");
        exit(EXIT_FAILURE);
    }

    printf("Taille du pipe en octets : %d\n", pipe_size);

    close(pipe_fd[0]);
    close(pipe_fd[1]);

    return 0;
}
