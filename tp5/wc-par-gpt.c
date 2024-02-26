#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_CHILDREN 4

int count_lines(char *filename, off_t start, off_t end) {
    int fd, count = 0;
    char ch;
    
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    lseek(fd, start, SEEK_SET);

    while (start < end && read(fd, &ch, 1) > 0) {
        if (ch == '\n') {
            count++;
        }
        start++;
    }

    close(fd);
    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *filename = argv[1];
    struct stat st;
    off_t file_size;

    if (stat(filename, &st) == -1) {
        perror("Erreur lors de la récupération des informations sur le fichier");
        exit(EXIT_FAILURE);
    }

    file_size = st.st_size;

    pid_t pid;
    int lines_count[MAX_CHILDREN] = {0};

    for (int i = 0; i < MAX_CHILDREN; i++) {
        off_t start = i * file_size / MAX_CHILDREN;
        off_t end = (i + 1) * file_size / MAX_CHILDREN;

        pid = fork();

        if (pid == 0) {
            // Dans le fils
            lines_count[i] = count_lines(filename, start, end);
            exit(lines_count[i]);
        } else if (pid < 0) {
            perror("Erreur lors de la création du fils");
            exit(EXIT_FAILURE);
        }
    }

    // Attendre la fin de tous les fils et récupérer leur code de retour
    int total_lines = 0;
    int child_status;

    for (int i = 0; i < MAX_CHILDREN; i++) {
        wait(&child_status);
        total_lines += WEXITSTATUS(child_status);
    }

    printf("Nombre total de lignes dans le fichier %s : %d\n", filename, total_lines);

    return 0;
}
