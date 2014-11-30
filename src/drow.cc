#include "drow.h"

#include "game.h"
#include "abstractEnemy.h"

/**
 *	Initialise Drow stats and set the racial ability (potion modifier).
 */
Drow::Drow() : Player(150, 25, 15) {
	Game::getInstance()->setPotionModifier(1.5);
}

/**
 *	Returns the player race
 */
std::string Drow::getRace() const {
	return "Drow";
}

/**
 *	Default getHitBy function, here as part of the Visitor pattern.
 */
void Drow::getHitBy(AbstractEnemy *e) {
	Character::getHitBy(static_cast<Character*>(e));
}

/**
 *	Dispatch function as part of the Visitor pattern.
 */
void Drow::strike(AbstractEnemy *e) {
	e->getHitBy(this);
}
