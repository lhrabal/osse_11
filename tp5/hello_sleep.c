#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread1_func(void *arg) {
    printf("h");
    fflush(stdout);
    sleep(1);
    printf("o");
    fflush(stdout);
    return NULL;
}

void *thread2_func(void *arg) {
    sleep(1);
    printf("ell");
    fflush(stdout);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread1_func, NULL);
    pthread_create(&thread2, NULL, thread2_func, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("\n");
    return 0;
}
