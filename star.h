/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

#pragma once

#include "position.h"
#include "uiDraw.h"
#include <random>




class Star 
{
public:
	Star();
	void draw(ogstream& gout) { drawStar(pos, phase); }
	void incrementPhase();

private:
	Position pos;
	unsigned char phase;
	bool phasePositive = true;
};
