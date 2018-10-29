#include "control.h"

PCA9685 Control::pwmController;
Motor *Control::driveFrontRight;
Motor *Control::driveFrontLeft;
Motor *Control::driveRearRight;
Motor *Control::driveRearLeft;

void Control::init(){
  pwmController.SetFrequency(440);

  /*
                                  phys(bcm)
    motor             _pwmChannel _fwdPin _revPin
    driveFrontRight   4           11(17)  13(27)
    driveFrontLeft    5           16(23)  15(22)
    driveRearRight    6           18(24)  22(25)
    driveRearLeft     7           29(05)  31(06)
  */

  driveFrontRight = new Motor(4, 17, 27);
  driveFrontLeft  = new Motor(5, 23, 22);
  driveRearRight  = new Motor(6, 24, 25);
  driveRearLeft   = new Motor(7,  5,  6);

  //TODO: Watchdog thread to check for control app timeout
  //TODO: Threaded ramping of servo position for smoothing.

  setLeftThrottle(0);
  setRightThrottle(0);
}

void Control::setLeftThrottle(double val){
  driveFrontLeft->setValue(val);
  driveRearLeft->setValue(val);
}

void Control::setRightThrottle(double val){
  driveFrontRight->setValue(val);
  driveRearRight->setValue(val);
}
