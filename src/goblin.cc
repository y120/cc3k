#include "goblin.h"

#include "game.h"
#include "abstractEnemy.h"
#include "turnSummary.h"
#include "orc.h"
#include <cmath>

/**
 *	Initialise Goblin stats.
 */
Goblin::Goblin() : Player(110, 15, 20) {}

/**
 *	Default getHitBy function, here as part of the Visitor pattern.
 */
void Goblin::getHitBy(AbstractEnemy *e) {
	Character::getHitBy(static_cast<Character*>(e));
}

/**
 *	Goblins take 50% more damage from Orcs!
 */
void Goblin::getHitBy(Orc *e) {
	// First check dodge.
	if (Game::getInstance()->rand(100) < this->getDodge()) {
		this->hit = false;
		return;
	}

	this->hit = true;
	this->addHP(-std::ceil(1.5 * this->calculateDamage(e)));
}

/**
 *	Dispatch function as part of the Visitor pattern.
 *
 *	Goblin racial ability: if the enemy dies, the Goblin also steals 5 gold.
 */
void Goblin::strike(AbstractEnemy *e) {
	e->getHitBy(this);
	if (e->isDead()) {
		this->addGold(5);
		TurnSummary::add("Player steals 5 gold from the corpse.");
	}
}
