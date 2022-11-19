/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

#pragma once

#include "entity.h"
#include "earth.h"
#include "uiDraw.h"

using namespace std;

class ShortLived : public Entity
{
public:
	ShortLived() : life(0), launchOffset(4.0) {}
	ShortLived(const Position& position, const Velocity& velocity) :
		life(0), launchOffset(4.0) {}
	ShortLived(const Position& position, const Velocity& velocity, double launchAngle) :
		life(0), launchOffset(4.0) {}
	virtual void advance(const Earth& earth) {}
	virtual void draw(ogstream& gout) = 0;

protected:
	int life;
	double launchOffset;
};