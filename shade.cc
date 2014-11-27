#include "shade.h"

#include "game.h"
#include "abstractEnemy.h"

/**
 *	Initialise Shade stats.
 */
Shade::Shade() : Player(125, 25, 25) {}

/**
 *	Default getHitBy function, here as part of the Visitor pattern.
 */
void Shade::getHitBy(AbstractEnemy *e) {
	Character::getHitBy(static_cast<Character*>(e));
}

/**
 *	Dispatch function as part of the Visitor pattern.
 */
void Shade::strike(AbstractEnemy *e) {
	e->getHitBy(this);
}
