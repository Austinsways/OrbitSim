#include "ship.h"

void Ship::accelerate(const Earth& earth)
{
   //double acc = 30.0 * earth.getTimePerFrame() / 60.0;  - No need to divide by 60
   double acc = 30.0 * earth.getTimePerFrame();
   velocity.applyAcceleration(Acceleration(angle, acc));
}

Projectile Ship::fire()
{
    return Projectile();
}
