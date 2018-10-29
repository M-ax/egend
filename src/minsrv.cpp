#include <iostream>
#include <string>
#include <chrono>

#include "minsrv.h"
#include "control.h"

using namespace std;
using namespace std::chrono;

MinSrv::MinSrv(const char *host, int port){
  this->host = host;
  this->port = port;

  //TODO: This has to be retarded, cast &onMessage to std::function somehow
  socketHub.onMessage(
    [this](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode) {
      this->onMessage(ws, message, length, opCode);
    }
  );
}

void MinSrv::run(){
  //if (socketHub.listen(host, port)){
  if (socketHub.listen(port)){
    cout << "Listening on " << host << ":" << port << "\n";
    socketHub.run();
  }
  else {
    cout << "Control backend is dead.  Socket collision?" << "\n";
  }
}

void MinSrv::onMessage(WebSocket<SERVER> *ws, char *message, size_t length, OpCode opCode){
  int64_t timestamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  //Null terminate after length, don't give a shit about protocol info.
  //GIMME THAT DATA
  message[length] = '\0';

  //Read useful information out of message.
  double leftThrottleVal, rightThrottleVal;
  leftThrottleVal = strtod(message, &message);
  rightThrottleVal = strtod(message, &message);

  cout << "left: " << leftThrottleVal
    << " ; right: " << rightThrottleVal
    << " ; hz: " << (1000. / (timestamp - lastMessageTime)) << "\n";

  Control::setLeftThrottle(leftThrottleVal);
  Control::setRightThrottle(rightThrottleVal);

  //ws->send("ACK", 3, opCode);

  lastMessageTime = timestamp;
}
