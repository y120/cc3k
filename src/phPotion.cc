#include "phPotion.h"
#include "game.h"
#include "player.h"

void PHPotion::apply() {
	Game::getInstance()->getPlayer()->addHP(-Game::getInstance()->getPotionStrength());
}

std::string PHPotion::getNameInternal() const {
	return "Poison Health Potion";
}
