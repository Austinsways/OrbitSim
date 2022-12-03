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

class CrewDragonCenter : public Satellite
{
public:
	CrewDragonCenter() : Satellite() { init(); }
	CrewDragonCenter(const Position& position, const Velocity& velocity, double angle = 0.0) : Satellite(position, velocity, angle) { init(); }
	std::list<std::shared_ptr<Entity>> destroy() { return createDestroyedList<Fragment, Fragment, Fragment, Fragment>(); }
	void draw(ogstream& gout) { drawCrewDragonCenter(position, angle); }

private:
	void init() { radius = 6.0; }
};
