#include "fcgio.h"

class MinSrv
{
private:
  int socket;
public:
  MinSrv(void);

  void listenForRequests();
  void processRequest(FCGX_Request);
};
