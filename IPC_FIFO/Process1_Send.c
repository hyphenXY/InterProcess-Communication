#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

int main() {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);
  int fd;

  mkfifo("fifo", 0666);
  char arr[50][11];
  for (int i = 0; i < 50; i++) {
    for (int j = 0; j < 11; j++) {
      arr[i][j] = 'a' + rand() % 26;
    }
  }
  fd = open("fifo", O_WRONLY);
  int id = 0;
  while (id < 50) {
    int n = 0;
    for (int i = id; i < id + 5 && i < 50; i++) {
      write(fd, &i, sizeof(i));
      write(fd, arr[i], 11);
      n++;
    }
    int ack;
    read(fd, &ack, sizeof(ack));
    printf("acknowledged id -> %d\n", ack);
    id = ack + 1;
  }

  close(fd);
  clock_gettime(CLOCK_MONOTONIC, &end);
  double time;
  time = (end.tv_sec - start.tv_sec) * 1e9;
  time = (time + (end.tv_nsec - start.tv_nsec)) * 1e-9;

  printf("Time taken: %f seconds  ", time);
  return 0;
}
