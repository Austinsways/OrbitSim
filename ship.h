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
#include "fragment.h"

#include <list>
#include <memory>

class TestShip;

/**************************************************
 * SHIP
 * The Dream Chaser Ship is controlled by the player and shoots Projectiles at Satellites
 **************************************************/
class Ship : public Entity
{
public:
   friend TestShip;

   Ship() : Entity() { init(); }
   Ship(const Position& pos, const Velocity& vel, double angle) : Entity(pos, vel, angle) { init(); }
   void turnLeft() { angle -= 0.1; }
   void turnRight() { angle += 0.1; }
   void accelerate(const Earth& earth);
   void setThrust(bool thrust) { this->thrust = thrust; }
   Projectile fire()
   {
      return Projectile(position, velocity, angle);
   }
   std::list<std::shared_ptr<Entity>> destroy() { return createDestroyedList<Fragment, Fragment, Fragment, Fragment, Fragment>(); }
   virtual void draw(ogstream& gout) { drawShip(position, angle, thrust); }

private:
   void init()
   {
      radius = 10.0;
      thrust = false;
   }
   bool thrust;
};
