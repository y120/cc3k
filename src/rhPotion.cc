#include "rhPotion.h"
#include "game.h"
#include "player.h"

void RHPotion::apply() {
	Game::getInstance()->getPlayer()->addHP(Game::getInstance()->getPotionStrength());
}

std::string RHPotion::getNameInternal() const {
	return "Restore Health Potion";
}
