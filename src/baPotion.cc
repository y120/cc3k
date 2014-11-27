#include "baPotion.h"

#include "fbModifyAtkEffect.h"
#include "game.h"

BAPotion::BAPotion() {
	this->effect = new FBModifyAtkEffect(NULL, Game::getInstance()->getFloorNumber(),
		Game::getInstance()->getPotionStrength());
}

std::string BAPotion::getNameInternal() const {
	return "Boost Attack Potion";
}
