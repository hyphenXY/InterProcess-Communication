#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main() {
  int s, c;
  socklen_t x;
  struct sockaddr_un sa, ca;
  s = socket(AF_UNIX, SOCK_STREAM, 0);
  sa.sun_family = AF_UNIX;
  strncpy(sa.sun_path, "socket", sizeof(sa.sun_path) - 1);
  unlink("socket");
  int res = bind(s, (struct sockaddr *)&sa, sizeof(struct sockaddr_un));
  listen(s, 5);
  x = sizeof(ca);
  c = accept(s, (struct sockaddr *)&ca, &x);
  int ack = -1;
  for (int x = 0; x < 50; x++) {
    int id;
    char arr[11];
    int nr = read(c, &id, sizeof(id));
    read(c, arr, 11);
    printf("received arr with ID %d -> %s\n", id, arr);
    ack = id;
  }

  write(c, &ack, sizeof(ack));

  close(c);
  close(s);

  return 0;
}
