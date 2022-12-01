/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

#pragma once

#include "acceleration.h"

class Velocity
{
public:
	Velocity() : dx(0.0), dy(0.0) {}
	Velocity(double dx, double dy) : dx(dx), dy(dy) {}
   double getDx() const { return dx; }
   double getDy() const { return dy; }
   void adjustDx(double dx) { this->dx += dx; }
   void adjustDy(double dy) { this->dy += dy; }
   void applyAcceleration(const Acceleration& acc, double t);

   bool operator==(const Velocity& rhs)
   {
      return dx == rhs.getDx() && dy == rhs.getDy();
   }
private:
   double dx;
   double dy;
};
