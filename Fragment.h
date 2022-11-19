/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

#pragma once

#include "shortLived.h"
#include "uiDraw.h"

class Fragment : public ShortLived
{
public:
   Fragment() {}
   Fragment(const Position& position, const Velocity& velocity) {}
   Fragment(const Position& position, const Velocity& velocity, float launchAngle) {}
   void draw(ogstream& gout) {}

private:
   void init() { life = (int)random(50.0, 100.0); }
};