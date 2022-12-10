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
#include "starlinkBody.h"
#include "starlinkArray.h"
#include "fragment.h"

#include <list>
#include <memory>

/**************************************************
 * STARLINK
 * A Starlink Satellite
 **************************************************/
class Starlink : public Satellite
{
public:
	Starlink() : Satellite() { init(); }
	Starlink(const Position& position, const Velocity& velocity, double angle = 0.0) : Satellite(position, velocity, angle) { init(); }
	std::list<std::shared_ptr<Entity>> destroy() { return createDestroyedList<StarlinkBody, StarlinkArray, Fragment, Fragment>();}
	void draw(ogstream& gout) { drawStarlink(position, angle); }

private:
	void init() { radius = 6.0; }
};
