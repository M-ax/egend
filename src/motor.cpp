#include "motor.h"
#include "control.h"

Motor::Motor(uint8_t channel, uint8_t fwdPin, uint8_t revPin){
  _pwmChannel = channel;
  _fwdPin = fwdPin;
  _revPin = revPin;

  //Set BCM function select to output for fwd/rev pins.
  bcm2835_gpio_fsel(_fwdPin, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(_revPin, BCM2835_GPIO_FSEL_OUTP);
}

void Motor::setValue(double val){
  if (val < 0){
    //Val is less than zero, reverse.
    //Set revPin high and fwdPin low
    bcm2835_gpio_write(_fwdPin, LOW);
    bcm2835_gpio_write(_revPin, HIGH);

    //Set val positive for PWM set.
    val *= -1;
  }
  else if (val > 0){
    //Val is greater than zero, forward.
    //Set revPin low and fwdPin high
    bcm2835_gpio_write(_fwdPin, HIGH);
    bcm2835_gpio_write(_revPin, LOW);
  }

  int scaledVal = val * PCA9685_VALUE_MAX;
  if (scaledVal == PCA9685_VALUE_MAX) scaledVal--;

  Control::pwmController.Write(CHANNEL(_pwmChannel), VALUE(scaledVal));
}
