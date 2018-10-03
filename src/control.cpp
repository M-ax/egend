#include "control.h"

Servo *Control::steeringServo;

void Control::init(){
  //Setup main library
  wiringPiSetupGpio();

  //Setup the servo output pin
  pinMode(18, PWM_OUTPUT);

  //Set PWM clock speeds.
  pwmSetMode(PWM_MODE_MS);
  pwmSetRange(2000);
  pwmSetClock(192);

  //Setup steering servo with prior tested good parameters
  Control::steeringServo = new Servo(18, 60, 260);

  //TODO: Watchdog thread to check for control app timeout

  delay(1000);
}

//TODO: Fix mapping of -1 to 1 to min and max
void Control::setSteeringPosition(double pos){
  steeringServo->setPosition(pos);
}

int Control::getSteeringPosition(){
  return Control::steeringServo->getPosition();
}
