/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

#pragma once

#include "entity.h"
#include "uiDraw.h"

using namespace std;

class Satellite : public Entity
{
public:
	Satellite() : breakOffset(4.0) {}
	Satellite(const Position& position, const Velocity& velocity) : breakOffset(4.0) {}
	Satellite(const Position& position, const Velocity& velocity, double breakAngle) : breakOffset(4.0) {}

	virtual void draw(ogstream& gout) = 0;

protected:
	double breakOffset;
};