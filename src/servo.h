#include <wiringPi.h>

class Servo {
private:
  int _hwpin, _hwmin, _hwmax, _hwpos, _hwmid;
  void internalSet();
public:
  Servo(int, int, int);
  void setPosition(double);
  double getPosition(void);
  void setToMin();
  void setToMax();
  void setToMidpoint();
};
