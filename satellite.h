/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

#pragma once

#include "entity.h"
#include "uiDraw.h"

#include <cmath>

using namespace std;

class Satellite : public Entity
{
public:
   Satellite() : Entity() {}
   Satellite(const Position& position, const Velocity& velocity, double angle = 0.0, bool launch = false) :
      Entity(position, velocity, angle, launch ? random(5000.0, 9000.0) : 0.0)
   {
      if (launch)
         angularVelocity = random(-0.1, 0.1);
   }
   virtual void draw(ogstream& gout) = 0;
};
