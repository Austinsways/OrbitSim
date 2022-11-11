#pragma once
#include "entity.h"

using namespace std;

class Shortlived : public Entity
{
protected:
	int life;
	float launchOffset;
public:
	Shortlived() {}
	Shortlived(Position position, Velocity velocity) {}
	Shortlived(Position position, Velocity velocity, float LaunchAngle) {}
	virtual int dropLife() {}
	virtual void draw() = 0;
};