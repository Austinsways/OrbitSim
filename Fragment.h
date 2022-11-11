#pragma once
#include "Shortlived.h"

using namespace std;

class Fragment : public Shortlived {
public:
	Fragment() {}
	Fragment(Position position, Velocity velocity) {}
	Fragment(Position position, Velocity velocity, float launchAngle) {}
	void draw(ogstream gout) {}
};