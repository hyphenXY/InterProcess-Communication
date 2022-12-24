#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int state[5];

sem_t spoon[5];
sem_t bowl[2];

void *philosopher(void *args) {
  int i = *((int *)args);
  while (1) {
    printf("philosopher %d -> thinking\n", i);
    state[i] = 0;
    sem_wait(&spoon[i]);
    sem_wait(&spoon[(i + 1) % 5]);
    sem_wait(&bowl[0]);
    sem_wait(&bowl[1]);

    sleep(1);

    if (state[i] == 0 && state[(i + 4) % 5] != 1 && state[(i + 1) % 5] != 1) {
      state[i] = 1;
      printf("philosopher %d -> eating\n", i);
    }

    sem_post(&spoon[i]);
    sem_post(&spoon[(i + 1) % 5]);
    sem_post(&bowl[0]);
    sem_post(&bowl[1]);
  }
  return NULL;
}

int main() {
  pthread_t tid[5];
  int parr[5];

  for (int i = 0; i < 5; i++) {
    sem_init(&spoon[i], 0, 1);
  }

  sem_init(&bowl[0], 0, 1);
  sem_init(&bowl[1], 0, 1);

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

  sem_destroy(&bowl[0]);
  sem_destroy(&bowl[1]);
  
  return 0;
}
