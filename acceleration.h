#pragma once

#include <cmath>

class Acceleration
{
public:
   Acceleration() : ddx(0.0), ddy(0.0) {}
   Acceleration(double direction, double magnitude) :
      ddx(cos(direction) * magnitude),
      ddy(sin(direction) * magnitude) {}
   virtual double getDdx() { return ddx; }
   virtual double getDdy() { return ddy; }

private:
   double ddx;
   double ddy;
};
