#define _GNU_SOURCE
// c'est pour que les flags soient déclarés

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    // pipe non nommé
    int pipefd[2];
    int p = pipe(pipefd);
    
    int pipe_size = fcntl(pipefd[0], F_GETPIPE_SZ);

    int n_char = 0;
    while (n_char < pipe_size)
    {
        n_char++;
        printf("%d caractères ont étés écrits dans le pipe.\n", n_char);
        write(pipefd[1], "p", 1);
    }

    printf("Le pipe avait une taille de %d bytes.\n", pipe_size);

    close(pipefd[0]);
    close(pipefd[1]);
    
    // pipe nommé
    char* path = "bendo";
    int named_p = mkfifo(path, 0777);

    pipefd[2] = open(path, O_WRONLY | O_NONBLOCK); // Non block pour débloquer le pipe
    p = pipe(pipefd);
    pipe_size = fcntl(pipefd[0], F_GETPIPE_SZ);    

    printf("La taille du pipe nommé est de %d bytes.\n", pipe_size);
    
    unlink(path);
    close(pipefd[0]);
    close(pipefd[1]);
    
    return 0;
}
