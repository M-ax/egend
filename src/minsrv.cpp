#include <iostream>
#include <string>

#include "minsrv.h"
#include "control.h"

using namespace std;

MinSrv::MinSrv(){
  //Init cgi socket to talk to Nginx
  this->socket = FCGX_OpenSocket("127.0.0.1:8000", 500);
  FCGX_Init();
}

void MinSrv::listenForRequests()
{
  FCGX_Request request;
  FCGX_InitRequest(&request, this->socket, 0);

  while (FCGX_Accept_r(&request) == 0) {
    processRequest(request);
  }
}

void MinSrv::processRequest(FCGX_Request request){
  //Make stream buffers for the request's in, out, and err
  fcgi_streambuf rInBuf(request.in);
  fcgi_streambuf rOutBuf(request.out);
  fcgi_streambuf rErrBuf(request.err);

  //Make streams on the buffers manage input and output
  std::istream rIn(&rInBuf);
  std::ostream rOut(&rOutBuf);
  std::ostream rErr(&rErrBuf);

  //Get the request uri and content length
  //Both set by Nginx fastcgi_param
  char *reqUri = FCGX_GetParam("REQUEST_URI", request.envp);
  char *contentLengthStr = FCGX_GetParam("CONTENT_LENGTH", request.envp);

  printf("Received request from user, URI: \"%s\"\n", reqUri);

  //Convert number string to usable number.
  unsigned long contentLength = 0;
  if (contentLengthStr){
    contentLength = strtol(contentLengthStr, &contentLengthStr, 10);

    //End pointer is null, content length was parsed correctly.
    if (!*contentLengthStr && contentLength > 0){
      //Read post data into buffer.
      char *buf = new char[contentLength + 1];
      rIn.read(buf, contentLength);

      /*
        Something with istream or fcgi_streambuf is fucky.
        Without setting a null terminator at the end, the buffer gets overrun
          with extra garbled data past the end.
      */
      buf[contentLength] = '\0';

      //Read useful information out of buffer.
      double throttleVal, steeringVal;
      throttleVal = -strtod(buf, &buf);
      steeringVal = strtod(buf, &buf);

      Control::setSteeringPosition(steeringVal);
    }
  }
  if (contentLength == 0) {
    //No POST content means client crisis
    printf("!! Content length zero or absent.  Stopping all motors.\n");

    //Respond and finish request.
    rOut << "Content-type: text/plain\r\n\r\n";
    return;
  }

  rOut
    //Write out headers
    << "Content-type: text/plain\r\n\r\n"

    //Then content
    << "Current servo position: " << Control::getSteeringPosition() << "\n"
    << "Request URI: " << reqUri;
}
