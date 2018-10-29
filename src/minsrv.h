#include <stdio.h>
#include <cstdint>
#include <uWS/uWS.h>

using namespace std;
using namespace uWS;

#ifndef MINSRV_H
#define MINSRV_H

class MinSrv {
private:
  Hub socketHub;
  const char *host;
  int port;
  int64_t lastMessageTime;
public:
  MinSrv(const char*, int);

  void run();
  void onMessage(WebSocket<SERVER>*, char*, size_t, OpCode);
};

#endif
