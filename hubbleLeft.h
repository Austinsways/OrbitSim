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
 * HUBBLE LEFT
 * The left piece of the Hubble telescope
 **************************************************/
class HubbleLeft : public Satellite
{
public:
	HubbleLeft() : Satellite() { init(); }
	HubbleLeft(const Position& position, const Velocity& velocity, double angle = 0.0) : Satellite(position, velocity, angle, true) { init(); }
	std::list<std::shared_ptr<Entity>> destroy() { return createDestroyedList<Fragment, Fragment>(); } 
	void draw(ogstream& gout) { drawHubbleLeft(position, angle); }

private:
	void init() { radius = 8.0; }
};
