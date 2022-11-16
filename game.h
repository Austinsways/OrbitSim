#pragma once

#include "position.h"
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

	Game() {}
	Game(const Position& ptUpperRight) : ptUpperRight(ptUpperRight) {}
	void advance() {};
	void draw() {};
	
private:
	Earth earth;
	// The Ship will live inside the list of entities, but we will keep a pointer to it for convenience.
	std::shared_ptr<Ship> ship;
	std::list<std::unique_ptr<Entity>> entities;
	void controlShip() {};
	void moveEntities() {};
	void handleCollisions() {};
	bool checkCollision(const Entity& eOne, const Entity& eTwo);
	bool checkCollision(const Entity& entity, const Earth& earth);

	Position ptUpperRight;
};
