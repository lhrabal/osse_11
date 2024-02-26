#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>



int main(int argc, char *argv[]) {
    // Vérification du nombre d'arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <fichier>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Ouverture du fichier en lecture seule
    int fd_read = open(argv[1], O_RDONLY);
    if (fd_read == -1) {
        error("Erreur lors de l'ouverture du fichier en lecture seule");
    }

    // Calcul de la taille du fichier
    off_t file_size = lseek(fd_read, 0, SEEK_END);
    if (file_size == -1) {
        error("Erreur lors du calcul de la taille du fichier");
    }

    // Allocation d'un tableau de taille t - 1
    char *buffer = (char *)malloc(file_size - 1);
    if (buffer == NULL) {
        error("Erreur lors de l'allocation de mémoire");
    }

    // Lecture des t - 1 premiers octets du fichier
    if (lseek(fd_read, 0, SEEK_SET) == -1) {
        error("Erreur lors du positionnement du curseur de lecture");
    }

    ssize_t bytes_read = read(fd_read, buffer, file_size - 1);
    if (bytes_read == -1) {
        error("Erreur lors de la lecture du fichier");
    }

    // Fermeture du fichier en lecture seule
    close(fd_read);

    // Réouverture du fichier en écriture seule avec troncature
    int fd_write = open(argv[1], O_WRONLY | O_TRUNC);
    if (fd_write == -1) {
        error("Erreur lors de l'ouverture du fichier en écriture seule avec troncature");
    }

    // Écriture du contenu du tableau dans le fichier
    if (write(fd_write, buffer, file_size - 1) == -1) {
        error("Erreur lors de l'écriture dans le fichier");
    }

    // Fermeture du fichier en écriture seule
    close(fd_write);

    // Libération de la mémoire allouée
    free(buffer);

    printf("Le dernier caractère a été supprimé avec succès.\n");

    return 0;
}
