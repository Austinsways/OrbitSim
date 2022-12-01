/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

#pragma once

#include "satellite.h"
#include "entity.h"
#include "position.h"
#include "velocity.h"
#include "fragment.h"

#include <list>
#include <memory>

class GPSLeft : public Satellite
{
public:
   GPSLeft() : Satellite() { init(); }
   GPSLeft(const Position& position, const Velocity& velocity, double angle) : Satellite(position, velocity, angle, true) { init(); }
   std::list<std::shared_ptr<Entity>> destroy() { return createDestroyedList<Fragment, Fragment, Fragment>(); }
   void draw(ogstream& gout) { drawGPSLeft(position, angle); }

private:
   void init() { radius = 8.0; }
};
