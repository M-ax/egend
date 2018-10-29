#include <cstdint>

#include <bcm2835.h>
#include <pca9685.h>

#ifndef MOTOR_H
#define MOTOR_H

class Motor {
private:
  uint8_t _pwmChannel, _fwdPin, _revPin;
public:
  Motor(uint8_t, uint8_t, uint8_t);

  void setValue(double);
};

#endif
