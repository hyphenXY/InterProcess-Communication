#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

sem_t spoon[5];

void *philosopher(void *args) {
  int i = *(int *)args;
  while (1) {
    printf("philosopher %d -> thinking\n", i);
    sem_wait(&spoon[i]);
    sem_wait(&spoon[(i + 1) % 5]);

    sleep(1);

    printf("philosopher %d -> eating\n", i);
    sem_post(&spoon[i]);
    sem_post(&spoon[(i + 1) % 5]);
  }
}

int main() {
  pthread_t tid[5];
  int parr[5];

  for (int i = 0; i < 5; i++) {
    sem_init(&spoon[i], 0, 1);
  }

  for (int i = 0; i < 5; i++) {
    parr[i] = i;
  }

  for (int i = 0; i < 5; i++) {
    pthread_create(&tid[i], NULL, philosopher, &parr[i]);
  }

  for (int i = 0; i < 5; i++) {
    pthread_join(tid[i], NULL);
  }

  for (int i = 0; i < 5; i++) {
    sem_destroy(&spoon[i]);
  }

  return 0;
}
