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

  /*
    [this](format){
      is;
      suck;
    }
  */
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
    cout << "Yo it ate shit homie" << "\n";
  }
}

void MinSrv::onMessage(WebSocket<SERVER> *ws, char *message, size_t length, OpCode opCode){
  long timestamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  //Null terminate after length, don't give a shit about protocol info.
  //GIMME THAT DATA
  message[length] = '\0';

  cout << "now: " << timestamp
    << "; last: " << lastMessageTime
    << "; hz: " << (1000. / (timestamp - lastMessageTime)) << "\n";

  //Read useful information out of message.
  double throttleVal, steeringVal;
  throttleVal = -strtod(message, &message);
  steeringVal = strtod(message, &message);

  Control::setSteeringPosition(steeringVal);

  //ws->send("ACK", 3, opCode);

  lastMessageTime = timestamp;
}
