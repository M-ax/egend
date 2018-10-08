#include <stdio.h>
#include <uWS/uWS.h>

using namespace std;
using namespace uWS;

class MinSrv {
private:
  Hub socketHub;
  const char *host;
  int port;
  long lastMessageTime;
public:
  MinSrv(const char*, int);

  void run();
  void onMessage(WebSocket<SERVER>*, char*, size_t, OpCode);
};
