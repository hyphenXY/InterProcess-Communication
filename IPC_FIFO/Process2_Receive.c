#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  int fd;

  fd = open("fifo", O_RDONLY);
  int ack = -1;
  for (int x = 0; x < 42; x++) {
    int id;
    char str[11];
    int nr = read(fd, &id, sizeof(id));
    read(fd, str, 11);
    printf("received arr with ID %d -> %s\n", id, str);
      ack = id;
  }

  write(fd, &ack, sizeof(ack));

  close(fd);

  return 0;
}
