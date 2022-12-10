/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <array>

#include "entity.h"
#include "earth.h"
#include "acceleration.h"
#include "projectile.h"

using namespace std;

/**************************************************
 * ENTITY :: ADVANCE
 * Move the Entity around the Earth
 **************************************************/
void Entity::advance(const Earth& earth)
{
   double t = earth.getTimePerFrame();
   Acceleration gravity = earth.calculateGravity(*this);
   velocity.applyAcceleration(gravity, t);
   double x = 
      position.getMetersX() +
      velocity.getDx() * t +
      0.5 * gravity.getDdx() * t * t;
   double y = 
      position.getMetersY() +
      velocity.getDy() * t +
      0.5 * gravity.getDdy() * t * t;

   position.setMetersX(x);
   position.setMetersY(y);

   angle += angularVelocity;
}
