#include "floorBoundEffect.h"
#include "game.h"

/**
 *	Pass the base through and set floor.
 */
FloorBoundEffect::FloorBoundEffect(Player *base, int floor)
	: AbstractPlayerEffect(base), floor(floor) {}

/**
 *	A FloorBoundEffect expires when the potion floor is not the current floor.
 */
bool FloorBoundEffect::isExpired() const {
	return this->floor != Game::getInstance()->getFloorNumber();
}
