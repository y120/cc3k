#include "abstractItem.h"

/**
 *	Constructor. Set the value and set the destroy flag to false.
 */
AbstractItem::AbstractItem(int value) : value(value), destroy(false) {}

// Destructor does nothing by default; it's here because it's virtual.
AbstractItem::~AbstractItem() {}

int AbstractItem::getValue() const {
	return this->value;
}

bool AbstractItem::shouldDestroy() const {
	return this->destroy;
}
