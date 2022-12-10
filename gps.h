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
#include "gpsLeft.h"
#include "gpsCenter.h"
#include "gpsRight.h"
#include "fragment.h"

#include <list>
#include <memory>

/**************************************************
 * GPS
 * A GPS Satellite
 **************************************************/
class GPS : public Satellite
{
public:
   GPS() : Satellite() { init(); }
   GPS(const Position& position, const Velocity& velocity, double angle = 0.0) : Satellite(position, velocity, angle) { init(); }
   std::list<std::shared_ptr<Entity>> destroy() { return createDestroyedList<GPSLeft, GPSCenter, Fragment, GPSRight, Fragment>(); }
   void draw(ogstream& gout) { drawGPS(position, angle); }

private:
   void init() { radius = 12.0; }
};
