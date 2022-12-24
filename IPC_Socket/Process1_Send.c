#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>
#include <unistd.h>

int main() {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  int s, l, res;
  struct sockaddr_un adr;
  s = socket(AF_UNIX, SOCK_STREAM, 0);
  char arr[50][11];
  for (int i = 0; i < 50; i++) {
    for (int j = 0; j < 11; j++) {
      arr[i][j] = 'a' + rand() % 26;
    }
  }
  memset(&adr, 0, sizeof(struct sockaddr_un));
  adr.sun_family = AF_UNIX;
  strncpy(adr.sun_path, "socket", sizeof(adr.sun_path) - 1);
  l = sizeof(adr);
  res = connect(s, (struct sockaddr *)&adr, l);
  int id = 0;
  while (id < 50) {
    int n = 0;
    for (int i = id*50; i < (id + 5)*50 && i < 50; i++) {
      write(s, &i, sizeof(i));
      write(s, arr[i], 11);
      n++;
    }
    int ack;
    read(s, &ack, sizeof(ack));
    printf("acknowledged id -> %d\n", ack);
    id = ack + 1;
  }

  close(s);

  clock_gettime(CLOCK_MONOTONIC, &end);
  double time;
  time = (end.tv_sec - start.tv_sec) * 1e9;
  time = (time + (end.tv_nsec - start.tv_nsec)) * 1e-9;

  printf("Time taken: %f seconds  ", time);

  return 0;
}
