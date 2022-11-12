#pragma once

#include "entity.h"
#include "uiDraw.h"

using namespace std;

class Satellite : public Entity {
protected:
	float breakOffset;
public:
	Satellite() {}
	Satellite(Position position, Velocity velocity) {}
	Satellite(Position position, Velocity velocity, double breakAngle) {}

	virtual void draw(ogstream& gout) = 0;
};