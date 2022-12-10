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
 * CREW DRAGON RIGHT
 * The right piece of the Crew Dragon
 **************************************************/
class CrewDragonRight : public Satellite
{
public:
	CrewDragonRight() : Satellite() { init(); }
	CrewDragonRight(const Position& position, const Velocity& velocity, double angle = 0.0) : Satellite(position, velocity, angle, true) { init(); }
	std::list<std::shared_ptr<Entity>> destroy() { return createDestroyedList<Fragment, Fragment>(); }
	void draw(ogstream& gout) { drawCrewDragonRight(position, angle); }

private:
	void init() { radius = 6.0; }
};
