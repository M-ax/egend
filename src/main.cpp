#include <stdio.h>
#include <iostream>
#include <thread>

#include "main.h"
#include "minsrv.h"
#include "control.h"

using namespace std;

int main(void)
{
  printf("EGEN 310 control app v0.1 starting...\n");

  printf("Setting up wiringPi parameters...\n");
  Control::init();

  // printf("Testing servo functionality...\n");
  // Control::steeringServo->setToMin();
  // delay(1000);
  // for (int i = Control::steeringServo->min;
  //   i <= Control::steeringServo->max; i++)
  // {
  //   Control::setSteeringPosition(i);
  //   delay(10);
  // }

  printf("Spawning server thread....\n");
  thread srvThread(serverThread);

  //Read command inputs on this thread
  string input;
  while (true){
    getline(cin, input);

    //TODO: Do things with input... maybe

    cout << input << "\n";
  }

  //printf("Waiting for server thread...\n");
  //srvThread will never come back :(
  srvThread.join();

  return 0;
}

void serverThread(void)
{
  MinSrv srv;

  while (true){
    srv.listenForRequests();
  }
}
