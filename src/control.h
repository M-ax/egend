#include <wiringPi.h>

#include "servo.h"

class Control
{
private:
  Control(void);


  //Motor driveLeftFront;
  //Motor driveRightFront;
  //Motor driveLeftRear;
  //Motor driveRightRear;
public:
  static Servo *steeringServo;

  static void init();
  static void setSteeringPosition(double);
  static int getSteeringPosition();
};
