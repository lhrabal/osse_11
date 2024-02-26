#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    // Création du premier fils
    printf("Père : Création du premier fils\n");
    pid_t p1_id = fork();

    if (p1_id == 0) {
        // Premier fils
        printf("Premier fils : Attente de 2 secondes\n");
        sleep(2);
        printf("\nPremier fils : Écriture de la nouvelle ligne\n\n");
        exit(0);
    }

    // Création du deuxième fils
    printf("Père : Création du deuxième fils\n");
    pid_t p2_id = fork();

    if (p2_id == 0) {
        // Deuxième fils
        printf("Deuxième fils : Attente de 1 seconde\n");
        sleep(1);
        printf("Deuxième fils : Écriture de ' world'\n");
        printf(" world");
        exit(0);
    }

    // Attente de la fin des deux fils
    printf("Père : Attente de la fin des fils\n");
    waitpid(p1_id, NULL, 0);
    waitpid(p2_id, NULL, 0);

    // Écriture de "hello"
    printf("hello");

    // Fin du programme
    printf("\nPère : Fin du programme\n");
    return 0;
}
