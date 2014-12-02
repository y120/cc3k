#include "goldPile.h"
#include "game.h"
#include "floor.h"
#include "tile.h"
#include "player.h"
#include <sstream>

namespace {
	void setGoldSprite(Renderable *obj) {
		obj->setSprite("G");
		obj->setColour(ColourType::DYELLOW);
	}
}

GoldPile::GoldPile(GoldPileSize size) : AbstractItem(static_cast<int>(size)) {
	setGoldSprite(this);
}

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
	oss << Game::getInstance()->getPlayer()->getName() << " picks up " << this->value << " gold.";
	Display::getInstance()->addMessage(oss.str());

	// delete it from floor
	Game::getInstance()->getFloor()->getTile(this->getR(), this->getC())->setContents(NULL);
}
