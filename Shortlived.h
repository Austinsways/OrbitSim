#pragma once

#include "entity.h"
#include "earth.h"
#include "uiDraw.h"

using namespace std;

class ShortLived : public Entity
{
protected:
	int life;
	float launchOffset;
public:
	ShortLived() {}
	ShortLived(Position position, Velocity velocity) {}
	ShortLived(Position position, Velocity velocity, double launchAngle) {}
	virtual void advance(const Earth& earth) {}
	virtual void draw(ogstream& gout) = 0;
};