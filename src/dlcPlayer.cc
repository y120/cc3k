#include "dlcPlayer.h"

#include "game.h"
#include "abstractEnemy.h"
#include "display.h"
#include <sstream>

/**
 *	Initialise SuperVillan stats.
 */
SuperVillan::SuperVillan() : Player(250, 99, 99) {}

/**
 *	Returns the player race
 */
std::string SuperVillan::getRace() const {
	return "SuperVillan";
}

/**
 *	Default getHitBy function, here as part of the Visitor pattern.
 */
void SuperVillan::getHitBy(AbstractEnemy *e) {
	Character::getHitBy(static_cast<Character*>(e));
}

/**
 *	Dispatch function as part of the Visitor pattern.
 */
void SuperVillan::strike(AbstractEnemy *e) {
	e->getHitBy(this);
}



/**
 *	Initialise VampTrol stats.
 *
 *	Technically, the VampTrol has no max HP. However, that's a bit annoying to
 *	implement; we'll just say it's unreasonable for HP to ever exceed 100k and
 *	set it to that.
 */
VampTrol::VampTrol() : Player(50, 25, 25) {
	this->setMaxHP(100000);
}

/**
 *	Returns the player race
 */
std::string VampTrol::getRace() const {
	return "VampTrol";
}

/**
 *	Default getHitBy function, here as part of the Visitor pattern.
 */
void VampTrol::getHitBy(AbstractEnemy *e) {
	Character::getHitBy(static_cast<Character*>(e));
}

/**
 *	Dispatch function as part of the Visitor pattern.
 *
 *	VampTrol racial ability: if it manages to land a hit on the enemy, then the
 *	vampire heals for 5 HP.
 */
void VampTrol::strike(AbstractEnemy *e) {
	e->getHitBy(this);
	if (e->wasHit()) {
		this->addHP(5);
		Display::getInstance()->addMessage(this->getName() + " stole 5 HP from " +
			e->getName() + "!");
	}
}

Player* VampTrol::tickEffects() {
	int dHP = this->getHP();
	this->addHP(5);
	dHP = this->getHP() - dHP;
	if (dHP) {
		std::ostringstream oss;
		oss << this->getName() << " regenerates " << dHP << " HP.";
		Display::getInstance()->addMessage(oss.str());
	}
	return this;
}