/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

#pragma once

#include "entity.h"
#include "earth.h"
#include "projectile.h"
#include "uiDraw.h"

class TestShip;

class Ship : public Entity
{
public:
   friend TestShip;

   Ship() : Entity() { thrust = false; }
   Ship(const Position& pos, const Velocity& vel, double angle) : Entity(pos, vel)
   {
      this->angle = angle;
      radius = 10.0;
      thrust = false;
   }
   void turnLeft() { angle -= 0.1; }
   void turnRight() { angle += 0.1; }
   void accelerate(const Earth& earth);
   void setThrust(bool thrust) { this->thrust = thrust; }
   Projectile fire();
   virtual void draw(ogstream& gout) { drawShip(position, angle, thrust); }

private:
   bool thrust;
};
