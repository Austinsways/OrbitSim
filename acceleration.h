/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

#pragma once

#include <cmath>

/**************************************************
 * ACCELERATION
 * Measured in meters/second^2
 **************************************************/
class Acceleration
{
public:
   Acceleration() : ddx(0.0), ddy(0.0) {}
   Acceleration(double direction, double magnitude) :
      ddx(sin(direction) * magnitude),
      ddy(cos(direction) * magnitude) {}
   virtual double getDdx() const { return ddx; }
   virtual double getDdy() const { return ddy; }

private:
   double ddx;
   double ddy;
};
