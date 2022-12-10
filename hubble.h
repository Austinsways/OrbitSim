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
#include "hubbleComputer.h"
#include "hubbleTelescope.h"
#include "hubbleLeft.h"
#include "hubbleRight.h"
#include "fragment.h"

#include <list>
#include <memory>

/**************************************************
 * HUBBLE
 * The Hubble telescope
 **************************************************/
class Hubble : public Satellite
{
public:
	Hubble() : Satellite() { init(); }
	Hubble (const Position& position, const Velocity& velocity, double angle = 0.0) : Satellite(position, velocity, angle) { init(); }
	std::list<std::shared_ptr<Entity>> destroy() { return createDestroyedList<HubbleTelescope, HubbleComputer, HubbleLeft, HubbleRight>(); } 
	void draw(ogstream& gout) { drawHubble(position, angle); }

private:
	void init() { radius = 10.0; }
};
