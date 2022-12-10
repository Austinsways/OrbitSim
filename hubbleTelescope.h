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
 * HUBBLE TELESCOPE
 * The telescope piece of the Hubble telescope
 **************************************************/
class HubbleTelescope : public Satellite
{
public:
	HubbleTelescope() : Satellite() { init(); }
	HubbleTelescope(const Position& position, const Velocity& velocity, double angle = 0.0) : Satellite(position, velocity, angle, true) { init(); }
	std::list<std::shared_ptr<Entity>> destroy() { return createDestroyedList<Fragment, Fragment, Fragment>(); }
	void draw(ogstream& gout) { drawHubbleTelescope(position, angle); }

private:
	void init() { radius = 10.0; }
};
