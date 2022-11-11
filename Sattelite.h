#pragma once
#include "entity.h"


using namespace std;

class Sattelite : public Entity {
protected:
	float breakOffset;
public:
	Sattelite() {}
	Sattelite(Position position, Velocity velocity) {}
	Sattelite(Position position, Velocity velocity, float BreakAngle) {}

	virtual void draw() = 0;
};