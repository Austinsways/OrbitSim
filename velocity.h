#pragma once

#include "acceleration.h"

class Velocity
{
public:
	Velocity() : dx(0.0), dy(0.0) {}
	Velocity(double dx, double dy) : dx(dx), dy(dy) {}
   double getDx() const { return dx; }
   double getDy() const { return dy; }
   void applyAcceleration(const Acceleration& acc);

   bool operator==(const Velocity& rhs)
   {
      return dx == rhs.getDx() && dy == rhs.getDy();
   }
private:
   double dx;
   double dy;
};
