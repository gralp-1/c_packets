#include "../common.h"

int main(void) {
  struct sockaddr_in si_me, si_other;
  int s, i, slen = sizeof(si_other);
  if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    diep("socket");
  memset((char *)&si_me, 0, sizeof(si_me));
  char buf[BUFLEN];

  si_me.sin_family = AF_INET;
  si_me.sin_port = htons(PORT);
  si_me.sin_addr.s_addr = htonl(INADDR_ANY);
  const struct sockaddr *si_me_ptr = (const struct sockaddr *)&si_me;
  if (bind(s, si_me_ptr, sizeof(si_me)) == -1)
    diep("bind");
  for (i = 0; i < NPACK; i++) {
    if (recvfrom(s, buf, BUFLEN, 0, &si_other, &slen) == -1)
      diep("recvfrom()");
    printf("Data: %d\n", pac_deserialize(buf).x);
  }
  close(s);
  return 0;
}
