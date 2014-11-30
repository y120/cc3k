#include "troll.h"

#include "game.h"
#include "abstractEnemy.h"

/**
 *	Initialise Troll stats.
 */
Troll::Troll() : Player(120, 25, 15) {}

/**
 *	Returns the player race
 */
std::string Troll::getRace() const {
	return "Troll";
}

/**
 *	Default getHitBy function, here as part of the Visitor pattern.
 */
void Troll::getHitBy(AbstractEnemy *e) {
	Character::getHitBy(static_cast<Character*>(e));
}

/**
 *	Dispatch function as part of the Visitor pattern.
 */
void Troll::strike(AbstractEnemy *e) {
	e->getHitBy(this);
}

/**
 *	Troll racial ability: regenerate 5 HP per turn.
 */
Player* Troll::tickEffects() {
	this->addHP(5);
	return this;
}
