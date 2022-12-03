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
#include "crewDragonCenter.h"
#include "crewDragonLeft.h"
#include "crewDragonRight.h"
#include "fragment.h"

#include <list>
#include <memory>

class CrewDragon : public Satellite
{
public:
	CrewDragon() : Satellite() { init(); }
	CrewDragon(const Position& position, const Velocity& velocity, double angle = 0.0) : Satellite(position, velocity, angle) { init(); }
	std::list<std::shared_ptr<Entity>> destroy() { return createDestroyedList<Fragment, Fragment, CrewDragonCenter, CrewDragonLeft, CrewDragonRight>(); }
	void draw(ogstream& gout) { drawCrewDragon(position, angle); }

private:
	void init() { radius = 7.0; }
};
