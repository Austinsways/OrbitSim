/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

#pragma once

#include "shortLived.h"

class Projectile : public ShortLived
{
public:
   Projectile() : ShortLived() { init(); }
   Projectile(const Position& position, const Velocity& velocity) : ShortLived(position, velocity) { init(); }
   Projectile(const Position& position, const Velocity& velocity, float launchAngle) : ShortLived(position, velocity, launchAngle) { init(); }
   void draw(ogstream& gout) {}

private:
   void init() { life = 70; }
};