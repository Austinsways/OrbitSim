#include "entity.h"
#include "earth.h"
#include "acceleration.h"

using namespace std;

void Entity::advance(const Earth& earth)
{
   double t = earth.getTimePerFrame();
   Acceleration gravity = earth.calculateGravity(*this);
   double x = position.getMetersX() +
      velocity.getDx() * t +
      0.5 * gravity.getDdx() * t * t;
   double y = position.getMetersY() +
      velocity.getDy() * t +
      0.5 * gravity.getDdy() * t * t;
   position.setMetersX(x);
   position.setMetersY(y);
}

list<shared_ptr<Entity>> Entity::destroy()
{
   return list<shared_ptr<Entity>>();
}
