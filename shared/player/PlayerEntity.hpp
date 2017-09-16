#pragma once

#include <string>

struct PlayerEntity {
	int positionX = 0, positionY = 0;
	int health = 0, maxHealth = 100;

	enum Team {
		RED,
		BLUE
	} team;

	std::string displayName = "DEFAULT";
};

