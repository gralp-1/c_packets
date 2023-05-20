#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define BUFLEN 512
#define NPACK 10
#define PORT 9930
#define BUFLEN 512

typedef struct Packet {
  int x;
} Packet;

void diep(char *s) {
  perror(s);
  exit(1);
}

char *pac_serialize(Packet pac) {
  char *buf = malloc(sizeof(Packet));
  memcpy(buf, &pac, sizeof(Packet));
  return buf;
}

Packet pac_deserialize(char *buf) {
  Packet *pac = malloc(sizeof(Packet));
  memcpy(pac, buf, sizeof(Packet));
  return *pac;
}
