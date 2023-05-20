#define NOBUILD_IMPLEMENTATION
#include "nobuild.h"
#include <time.h>
#define CFLAGS "-Wall", "-pedantic", "-O3", "-g"

int build_server() {
  CMD("cc", CFLAGS, "-o", NOEXT("server.c"), "./src/server/server.c");
  return 0;
}
int build_client() {
  CMD("cc", CFLAGS, "-o", NOEXT("client.c"), "./src/client/client.c");
  return 0;
}

int main(int argc, char **argv) {
  GO_REBUILD_URSELF(argc, argv);
  // if arguments contain server, build server
  if (argc > 1 && strcmp(argv[1], "server") == 0) {
    build_server();
    return 0;
  } else if (argc > 1 && strcmp(argv[1], "client") == 0) {
    build_client();
    return 0;
  }

  build_client();
  build_server();

  RM("./client.dSYM");
  RM("./server.dSYM");

  return 0;
}
