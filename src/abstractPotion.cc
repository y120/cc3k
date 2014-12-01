#include "abstractPotion.h"
#include "game.h"
#include "dlc.h"
#include "player.h"
#include "inventory.h"
#include "abstractPlayerEffect.h"

std::set<std::string> AbstractPotion::discoveredPotions;

namespace {
	void setPotionSprite(Renderable *obj) {
		obj->setSprite("P");
	}
}

/**
 *	By default, set effect to null. Also, set potion value to be the (unmodified)
 *	potion strength.
 */
AbstractPotion::AbstractPotion()
	: AbstractItem(Game::getInstance()->getPotionStrength(false))
	, effect(NULL)
{
	setPotionSprite(this);
}

/**
 *	Delete the effect. If effect is NULL, this won't do anything.
 */
AbstractPotion::~AbstractPotion() {
	delete this->effect;
}

/**
 *	Fetches the name for the potion, or a default string if undiscovered.
 *
 *	@param forceShow
 *		When set to true, will always show name.
 */
std::string AbstractPotion::getName(bool forceShow) const {
	if (forceShow || AbstractPotion::hasDiscovered(this->getNameInternal())) {
		return this->getNameInternal();
	} else {
		return "Unknown potion. Caveat usor.";
	}
}

/**
 *	Returns true if the specified potion has already been discovered.
 */
bool AbstractPotion::hasDiscovered(std::string name) {
	return static_cast<bool>(AbstractPotion::discoveredPotions.count(name));
}

/**
 *	Marks this particular potion as discovered.
 */
void AbstractPotion::discover() const {
	AbstractPotion::discoveredPotions.insert(this->getNameInternal());
}

/**
 *	The default application is to just add the effect as a decorator on the
 *	Player.
 */
void AbstractPotion::apply() {
	// Game::addPlayerEffect() will make a copy of the AbstractEffect. It also
	// handles the NULL case for us.
	Game::getInstance()->addPlayerEffect(this->effect);
	// When we use a potion, we automatically discover it!
	this->discover();
}

/**
 *	Potions can be picked up only if the Inventory DLC is active.
 */
bool AbstractPotion::canPickUp() const {
	return Game::getInstance()->hasDLC(DLC::Inventory);
}

/**
 *	If the Inventory DLC is active, then add it to the Player's inventory.
 */
void AbstractPotion::pickUp() {
	if (!Game::getInstance()->hasDLC(DLC::Inventory)) {
		return;
	}
	Game::getInstance()->getPlayer()->getInventory()->addItem(this);
}
