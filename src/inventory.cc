#include "inventory.h"

#include "abstractItem.h"

/**
 *	Initialise capacity and reserve vector.
 */
Inventory::Inventory(int capacity) : capacity(capacity) {
	this->contents.reserve(capacity);
}

/**
 *	On deletion, the Inventory should delete any associated items.
 */
Inventory::~Inventory() {
	for (std::vector<AbstractItem*>::iterator i = contents.begin();
		i != contents.end(); ++i) {
		delete *i;
	}
}

/**
 *	Gets the size of the inventory.
 */
unsigned Inventory::getSize() const {
	return this->contents.size();
}

/**
 *	Gets the total capacity of the inventory.
 */
unsigned Inventory::getCapacity() const {
	return this->capacity;
}

/**
 *	Sets the capacity of the inventory.
 *
 *	Note that if the current size exceeds capacity, items will not be dropped,
 *	but no new items may be picked up.
 */
void Inventory::setCapacity(int capacity) {
	this->capacity = capacity < 0 ? 0 : capacity;
}

/**
 *	Adds to the capacity. See note above on ::setCapacity().
 */
void Inventory::addCapacity(int d) {
	this->setCapacity(this->getCapacity() + d);
}

/**
 *	Potentially adds an item to the inventory. Returns whether the operation
 *	succeeded or not.
 */
bool Inventory::addItem(AbstractItem *item) {
	if (this->getSize() >= this->getCapacity()) {
		return false;
	}
	contents.push_back(item);
	return true;
}

/**
 *	Returns the item at a specific index, or NULL if none.
 */
AbstractItem* Inventory::getItem(unsigned index) const {
	return (index >= this->getSize()) ? this->contents[index] : NULL;
}

/**
 *	Removes and deletes a specific item.
 */
void Inventory::removeItem(unsigned index) {
	if (index >= this->getSize()) {
		return;
	}

	delete this->contents[index];
	this->contents.erase(this->contents.begin() + index);
}

std::vector<AbstractItem*>& Inventory::getRaw() {
	return this->contents;
}
