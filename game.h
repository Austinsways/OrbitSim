#pragma once
#pragma once

#include "entity.h"
#include "earth.h"
#include "uiDraw.h"
#include "ship.h"

#include <vector>
#include <list>
#include <memory>

class TestGame;

class Game 
{
public:
	friend TestGame;

	void advance() {};
	void draw() {};
	
private:
	Earth earth;
	// The Ship will live inside the list of entities, but we will keep a pointer to it for convenience.
	shared_ptr<Ship> ship;
	std::list<Entity> entities;
	void controlShip() {};
	void moveEntitys() {};
	void handleCollisions() {};
	bool checkCollision(Entity &eOne, Entity &eTwo) {};
	bool checkCollision(Entity &entity, Earth &earth) {};
};
