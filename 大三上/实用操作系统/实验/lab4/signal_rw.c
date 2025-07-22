#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t resource;
sem_t read_mutex;
int readCount = 0;

void* reader(void* arg) {
    int id = *((int*)arg);
    while(1) {
        sem_wait(&read_mutex);
        readCount++;
        if (readCount == 1) {
            sem_wait(&resource);
        }
        sem_post(&read_mutex);

        printf("Reader %d is reading.\n", id);
        sleep(3);

        sem_wait(&read_mutex);
        readCount--;
        if (readCount == 0) {
            sem_post(&resource);
        }
        sem_post(&read_mutex);

        sleep(1);
    }
}

void* writer(void* arg) {
    int id = *((int*)arg);
    while(1) {
        sem_wait(&resource);

        printf("Writer %d is writing.\n", id);
        sleep(1);

        sem_post(&resource);

        sleep(1);
    }
}

int main() {
    pthread_t r1, r2, w1;
    int id1 = 1, id2 = 2, id3 = 1;

    sem_init(&resource, 0, 1);
    sem_init(&read_mutex, 0, 1);

    pthread_create(&r1, NULL, reader, &id1);
    pthread_create(&r2, NULL, reader, &id2);
    pthread_create(&w1, NULL, writer, &id3);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w1, NULL);

    sem_destroy(&resource);
    sem_destroy(&read_mutex);

    return 0;
}
