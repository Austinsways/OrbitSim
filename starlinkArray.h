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

/**************************************************
 * STARLINK ARRAY
 * The solar array of a Starlink Satellite
 **************************************************/
class StarlinkArray : public Satellite
{
public:
	StarlinkArray() : Satellite() { init(); }
	StarlinkArray(const Position& position, const Velocity& velocity, double angle = 0.0) : Satellite(position, velocity, angle, true) { init(); }
	std::list<std::shared_ptr<Entity>> destroy() { return createDestroyedList<Fragment, Fragment, Fragment>(); }
	void draw(ogstream& gout) { drawStarlinkArray(position, angle); }

private:
	void init() { radius = 4.0; }
};
