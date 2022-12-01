/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

#pragma once

#include "entity.h"
#include "earth.h"
#include "uiDraw.h"

using namespace std;

class ShortLived : public Entity
{
public:
   ShortLived() : Entity(), life(0) {}
   ShortLived(const Position& position, const Velocity& velocity, double angle = 0.0, double launchSpeed = 0.0, double launchOffset = 0.0) :
      Entity(position, velocity, angle, launchSpeed, launchOffset),
      life(0)
   {
   }
   virtual void advance(const Earth& earth)
   {
      // Call the parent advance function
      Entity::advance(earth);
      // Tick down the life counter
      life--;
      if (life <= 0)
         dead = true;
   }
   virtual void draw(ogstream& gout) = 0;

protected:
   int life;
};
