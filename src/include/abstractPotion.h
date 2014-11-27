#ifndef __ABSTRACT_POTION_H__
#define __ABSTRACT_POTION_H__

#include "abstractItem.h"
#include <set>
#include <string>

class AbstractPlayerEffect;

class AbstractPotion : public AbstractItem {
public:
	AbstractPotion();
	virtual ~AbstractPotion();

	// When passed true, shows even if not discovered.
	std::string getName(bool) const;

	// Returns true if we've "discovered" a potion.
	static bool hasDiscovered(std::string);

	// Adds the current potion to the list of discovered potions.
	void discover() const;

	// Applies the effect of the potion. The potion should be destroyed after
	// this function is called.
	virtual void apply();

	bool canPickUp() const;
	void pickUp();

	std::string render();

protected:
	AbstractPlayerEffect *effect;

	static std::set<std::string> discoveredPotions;

	// Gets the actual name/description string.
	virtual std::string getNameInternal() const = 0;
};

#endif
