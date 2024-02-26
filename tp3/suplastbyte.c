#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    const char *path = argv[1];

    if (argc != 2)
    {
        fprintf(stderr, "Usage : ./suplastbyte <file>.\n");
        return 1;
    }

    int fd = open(path, O_RDWR);

    if (fd == -1)
    {
        fprintf(stderr, "Error : The file doesn't exist.\n");
        return 1;
    }

    // get the file size
    off_t size = lseek(fd, 0, SEEK_END);
    if (size == -1)
    {
        fprintf(stderr, "Error : mauvais calcul de la taille du fichier.\n");
        return 1;
    }

    // read and store the file's content
    char* tab = (char*) malloc(size - 1);

    // set the cursor at the file begining
    lseek(fd, 0, SEEK_SET);

    if (read(fd, tab, size - 1) == -1)
    {
        fprintf(stderr, "Error : Error while trying to read the file.\n");
        return 1;
    }

    for (int i = 0; i < size; i++) {
        printf("%c", tab[i]);
    }

    close(fd);

    // rewrite the content without the last char
    fd = open(path, O_WRONLY | O_TRUNC);
    if (write(fd, tab, size - 1) == -1) {
        fprintf(stderr, "Error : Error while trying to read the file.\n");
        return 1;
    }

    close(fd);

    return 0;
}
