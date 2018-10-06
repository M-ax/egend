#include <stdio.h>
#include <uWS/uWS.h>

using namespace std;
using namespace uWS;

class MinSrv
{
private:
  int socket;
public:
  MinSrv(void);

  void listenForRequests();
  void onRequest(WebSocket<SERVER>*, char*, size_t, OpCode);
};
