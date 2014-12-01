#include "phPotion.h"
#include "game.h"
#include "player.h"
#include "display.h"
#include <sstream>

void PHPotion::apply() {
	int dhp = std::min(Game::getInstance()->getPlayer()->getHP(),
		2 * Game::getInstance()->getPotionStrength());
	std::ostringstream oss;
	oss << Game::getInstance()->getPlayer()->getName() << " takes " << dhp <<
		" damage!";
	Display::getInstance()->addMessage(oss.str());
	Game::getInstance()->getPlayer()->addHP(-dhp);
	AbstractPotion::apply();
}

std::string PHPotion::getNameInternal() const {
	return "Poison Health Potion";
}
