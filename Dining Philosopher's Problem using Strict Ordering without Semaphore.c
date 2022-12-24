#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int spoons[5];
pthread_mutex_t mutex;

void *philosopher(void *args) {
  int i = *(int *)args;

  while (1) {
    printf("philosopher %d -> thinking\n", i);
    pthread_mutex_lock(&mutex);
    if (spoons[i] == 0 && spoons[(i + 1) % 5] == 0) {
      spoons[(i + 1) % 5] = 1;
      spoons[i] = 1;
      
      printf("philosopher %d -> eating\n", i);
      sleep(1);
      spoons[i] = 0;
      spoons[(i + 1) % 5] = 0;
    }
    pthread_mutex_unlock(&mutex);
  }
}

int main() {
  pthread_t tid[5];
  int parr[5];
  for (int i = 0; i < 5; i++) {
    spoons[i] = 0;
  }

  pthread_mutex_init(&mutex, NULL);

  for (int i = 0; i < 5; i++) {
    parr[i] = i;
  }

  for (int i = 0; i < 5; i++) {
    pthread_create(&tid[i], NULL, philosopher, &parr[i]);
  }

  for (int i = 0; i < 5; i++) {
    pthread_join(tid[i], NULL);
  }

  pthread_mutex_destroy(&mutex);

  return 0;
}
