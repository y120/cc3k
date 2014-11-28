#include "human.h"

#include "game.h"
#include "player.h"
#include "tile.h"
#include "goldPile.h"
#include "turnSummary.h"
#include <vector>
#include <sstream>

Human::Human() : AbstractEnemy(100, 20, 30) {}

/**
 *	Default getHitBy function, here as part of the Visitor pattern.
 */
void Human::getHitBy(Player *p) {
	Character::getHitBy(static_cast<Character*>(p));
}

/**
 *	Dispatch function as part of the Visitor pattern.
 */
void Human::strike(Player *p) {
	p->getHitBy(this);
}

/**
 *	Human racial ability: drops two normal gold piles.
 *	They had a family to support. You monster.
 */
void Human::die() {
	Tile *tile = this->getTile();
	if (Game::getInstance()->hasDLC(DLC::Inventory)) {
		// Humans will drop gold onto their current Tile.
		// They'll also drop one onto a random nearby unoccupied Tile.
		// If none exists, we merge the piles into a Merchant Hoard.
		std::vector<Tile*> unoccupied = tile->getUnoccupiedNeighbours();
		if (unoccupied.size() == 0) {
			// No valid tile: generate and place a MerchantHoard.
			tile->setContents(new GoldPile(GoldPile::MerchantHoard));
		} else {
			// Place both.
			Tile *tile2 = unoccupied[Game::getInstance()->rand(unoccupied.size())];
			tile->setContents(new GoldPile(GoldPile::NormalPile));
			tile2->setContents(new GoldPile(GoldPile::NormalPile));
		}
	} else {
		// Without the Inventory DLC, add the gold directly.
		int gold = static_cast<int>(GoldPile::NormalPile) * 2;
		Game::getInstance()->getPlayer()->addGold(gold);

		// Also log it...
		std::ostringstream oss;
		oss << "Player picked up " << gold << " gold!";
		TurnSummary::add(oss.str());

		// ... and clear the Tile.
		tile->setContents(NULL);
	}

	// Finally, call the base death handler.
	Character::die();
}

std::string Human::render() {
	return "H";
}
