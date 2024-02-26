#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUF_SIZE 1

int main()
{
    int pipe_fd[2];
    char buffer[BUF_SIZE];
    int bytes_written = 0;

    if (pipe(pipe_fd) == -1)
    {
        perror("Erreur lors de la création du pipe");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        if (write(pipe_fd[1], buffer, BUF_SIZE) != BUF_SIZE)
        {
            perror("Erreur lors de l'écriture dans le pipe");
            break;
        }
        bytes_written += BUF_SIZE;
        printf("Octets écrits dans le pipe : %d\n", bytes_written);
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);

    return 0;
}
