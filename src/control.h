#include "motor.h"

#ifndef CONTROL_H
#define CONTROL_H

class Control {
private:
  Control(void);
public:
  static PCA9685 pwmController;
  static Motor *driveFrontRight;
  static Motor *driveFrontLeft;
  static Motor *driveRearRight;
  static Motor *driveRearLeft;

  static void init();
  static void setLeftThrottle(double);
  static void setRightThrottle(double);
};

#endif
