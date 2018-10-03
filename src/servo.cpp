#include "servo.h"

Servo::Servo(int pin, int min, int max){
  this->_hwpin = pin;
  this->_hwmin = min;
  this->_hwmax = max;
  this->_hwmid = min + (max - min) / 2;
  setToMidpoint();
}

void Servo::internalSet(){
  pwmWrite(_hwpin, _hwpos);
}

void Servo::setPosition(double pos){
  if (pos < -1)
    pos = -1;
  else if (pos > 1)
    pos = 1;

  //Math magic to map from [-1, 1] to [_hwmin, _hwmax]
  //Pivot about 0, _hwmid
  _hwpos = _hwmid + ((_hwmid - _hwmin) * pos);
  internalSet();
}

double Servo::getPosition(){
  return 0;
}

void Servo::setToMin(){
  setPosition(_hwmin);
}

void Servo::setToMax(){
  setPosition(_hwmax);
}

void Servo::setToMidpoint(){
  setPosition(_hwmid);
}
