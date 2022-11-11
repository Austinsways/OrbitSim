#pragma once
#pragma once

#include "entity.h"
#include "earth.h"
#include "uiDraw.h"
#include "chaser.h"
#include <vector>
//include dreamchaser
using namespace std;

class TestGame;

class Game 
{
public:
	friend TestGame;

	void advance() {};
	void draw() {};

	
private:
	Earth earth;
	Chaser dreamChaser;
	vector<Entity> entitys[]; //this needs to be a vector currently because Entity is abstract
	void control() {};
	void moveEntitys() {};
	void handleCollisions() {};
	bool checkCollision(Entity &eOne, Entity &eTwo) {};
	bool checkCollision(Entity &eOne, Earth &eTwo) {};
};
