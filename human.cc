#include "human.h"

#include "game.h"
#include "player.h"
#include "tile.h"
#include "goldPile.h"
#include <vector>

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
	// Humans will drop gold onto their current Tile.
	// They'll also drop one onto a random nearby unoccupied Tile.
	// If none exists, we merge the piles into a Merchant Hoard.
	Tile *tile = this->getTile();

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

	// Finally, call the base death handler.
	Character::die();
}

std::string Human::render() {
	return "H";
}
