#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread1_func(void *arg) {
    pthread_mutex_lock(&mutex);
    printf("h");
    fflush(stdout);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *thread2_func(void *arg) {
    pthread_mutex_lock(&mutex);
    printf("ell");
    fflush(stdout);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread1_func, NULL);
    pthread_create(&thread2, NULL, thread2_func, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("o\n");

    return 0;
}
