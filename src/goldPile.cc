#include "goldPile.h"
#include "game.h"
#include "player.h"
#include "turnSummary.h"
#include <sstream>

GoldPile::GoldPile(GoldPileSize size) : AbstractItem(static_cast<int>(size)) {}

/**
 *	Whether the GoldPile can be picked up. By default, this is always true.
 */
bool GoldPile::canPickUp() const {
	return true;
}

/**
 *	On pickup, the Player gains the gold. Duh. Also leave a message.
 */
void GoldPile::pickUp() {
	Game::getInstance()->getPlayer()->addGold(this->value);

	std::ostringstream oss;
	oss << "Player picks up " << this->value << " gold.";
	TurnSummary::add(oss.str());
}

std::string GoldPile::render() {
	return "G";
}
