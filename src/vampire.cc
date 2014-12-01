#include "vampire.h"

#include "game.h"
#include "abstractEnemy.h"
#include "display.h"
#include "dwarf.h"

/**
 *	Initialise Vampire stats.
 *
 *	Technically, the Vampire has no max HP. However, that's a bit annoying to
 *	implement; we'll just say it's unreasonable for HP to ever exceed 100k and
 *	set it to that.
 */
Vampire::Vampire() : Player(50, 25, 25) {
	this->setMaxHP(100000);
}

/**
 *	Returns the player race
 */
std::string Vampire::getRace() const {
	return "Vampire";
}

/**
 *	Default getHitBy function, here as part of the Visitor pattern.
 */
void Vampire::getHitBy(AbstractEnemy *e) {
	Character::getHitBy(static_cast<Character*>(e));
}

/**
 *	Dispatch function as part of the Visitor pattern.
 *
 *	Vampire racial ability: if it manages to land a hit on the enemy, then the
 *	vampire heals for 5 HP.
 */
void Vampire::strike(AbstractEnemy *e) {
	e->getHitBy(this);
	if (e->wasHit()) {
		if (dynamic_cast<Dwarf*>(e)) {
			this->addHP(-5);
			Display::getInstance()->addMessage(this->getName() + " was poisoned" +
				" by " + e->getName() + "'s blood for 5 HP!");
		} else {
			this->addHP(5);
			Display::getInstance()->addMessage(this->getName() + " stole 5 HP from " +
				e->getName() + "!");
		}
	}
}
