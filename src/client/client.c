#define SRV_IP "192.168.1.148"

#include "../common.h"

// make a random 5 digit integer
int rand_int() {
  int r = 0;
  for (int i = 0; i < 5; i++) {
    r *= 10;
    r += rand() % 10;
  }
  return r;
}

int main(void) {
  // RANDOM INITIALIZATION
  time_t t;
  srand((unsigned)time(&t));

  // SOCKET INITIALIZATION
  struct sockaddr_in si_other;
  int s, i, slen = sizeof(si_other);
  char buf[BUFLEN];
  if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    diep("socket");
  memset((char *)&si_other, 0, sizeof(si_other));
  si_other.sin_family = AF_INET;
  si_other.sin_port = htons(PORT);
  if (inet_aton(SRV_IP, &si_other.sin_addr) == 0) {
    fprintf(stderr, "inet_aton() failed\n");
    exit(1);
  }

  // SENDING PACKETS
  for (i = 0; i < NPACK; i++) {
    Packet pac = {rand_int()};
    printf("%d\n", pac.x);
    if (sendto(s, pac_serialize(pac), BUFLEN, 0, &si_other, slen) == -1)
      diep("sendto()");
  }

  // CLEANUP
  close(s);
  return 0;
}
