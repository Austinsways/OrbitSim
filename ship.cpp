#include "ship.h"

void Ship::accelerate(const Earth& earth)
{
   double acc = 30.0 / 60.0;
   velocity.applyAcceleration(Acceleration(angle, acc), earth.getTimePerFrame());
}

Projectile Ship::fire()
{
    return Projectile();
}
